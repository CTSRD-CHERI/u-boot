@Library('ctsrd-jenkins-scripts') _

class GlobalVars { // "Groovy"
    public static boolean archiveArtifacts = false
}

echo("JOB_NAME='${env.JOB_NAME}', JOB_BASE_NAME='${env.JOB_BASE_NAME}'")
def rateLimit = rateLimitBuilds(throttle: [count: 1, durationName: 'hour', userBoost: true])

// Set job properties:
def jobProperties = [[$class: 'GithubProjectProperty', displayName: '', projectUrlStr: 'https://github.com/CTSRD-CHERI/u-boot/'],
                     copyArtifactPermission('*'), // Downstream jobs (may) need the kernels/disk images
                     rateLimit]
// Don't archive binaries for pull requests and non-default branches:
def archiveBranches = ['cheri']
//if (!env.CHANGE_ID && archiveBranches.contains(env.BRANCH_NAME)) {
    GlobalVars.archiveArtifacts = true
//}

def paramsArray = []

// Add an architecture selector for manual builds
def allArchitectures = ["riscv64", "riscv64-hybrid"]
paramsArray.add(text(defaultValue: allArchitectures.join('\n'),
        description: 'The architectures (cheribuild suffixes) to build for (one per line)',
        name: 'architectures'))

jobProperties.add(parameters(paramsArray))
// Set the default job properties (work around properties() not being additive but replacing)
setDefaultJobProperties(jobProperties)

jobs = [:]

def maybeArchiveArtifacts(params, String architecture) {
    if (GlobalVars.archiveArtifacts) {
        stage("Archiving artifacts") {
            sh """
mkdir -p artifacts-${architecture}
cp tarball/opt/u-boot-baremetal-${architecture}/u-boot* artifacts-${architecture}
"""
            archiveArtifacts allowEmptyArchive: false, artifacts: "artifacts-${architecture}/u-boot*", fingerprint: true, onlyIfSuccessful: true
        }
    }
}

// Work around for https://issues.jenkins.io/browse/JENKINS-46941
// Jenkins appears to use the last selected manual override for automatically triggered builds.
// Therefore, only read the parameter value for manually-triggered builds.
def selectedArchitectures = isManualBuild() && params.architectures != null ? params.architectures.split('\n') : allArchitectures
echo("Selected architectures: ${selectedArchitectures}")
selectedArchitectures.each { architecture ->
    jobs[architecture] = { ->
        cheribuildProject(target: "u-boot-baremetal-${architecture}",
                customGitCheckoutDir: 'u-boot',
                skipArchiving: true, skipTarball: true,
                sdkCompilerOnly: true,
                gitHubStatusContext: "ci/${architecture}",
                // Delete stale compiler/sysroot
                beforeBuild: { params ->
                    dir('cherisdk') { deleteDir() }
                    sh label: 'Deleting outputs from previous builds', script: 'rm -rfv artifacts-*'
                },
                afterBuild: { params -> maybeArchiveArtifacts(params, architecture) })
    }
}

boolean runParallel = true
echo("Running jobs in parallel: ${runParallel}")
if (runParallel) {
    jobs.failFast = false
    parallel jobs
} else {
    jobs.each { key, value ->
        echo("RUNNING ${key}")
        value()
    }
}
