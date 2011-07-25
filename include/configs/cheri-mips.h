/*
 * This file contains the configuration parameters for cheri-mips target.
 *    Very basic for the time being.  Needs to expand!
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MIPS64		1

/* Cache layout. */
#define CONFIG_SYS_ICACHE_SIZE		4096	/* 4 KByte total	*/
#define CONFIG_SYS_ICACHELINE_SIZE	8	/* 8 bytes/line		*/
#define CONFIG_SYS_DCACHE_SIZE		4096	/* 4 KByte total	*/
#define CONFIG_SYS_DCACHELINE_SIZE	8	/* 8 bytes/line		*/

#endif /* __CONFIG_H */
