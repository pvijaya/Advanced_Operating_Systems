#define AM335X_PADCTL_PEN	0x00000008	/* Pull up-down enabled	*/
#define AM335X_PADCTL_PUP	0x00000010	/* Pull up selected	*/
#define AM335X_PADCTL_PDN	0x00000000	/* Pull down selected	*/
#define AM335X_PADCTL_RXTX	0x00000020	/* Input or Output mode	*/
#define AM335X_PADCTL_TX	0x00000000	/* Output only mode	*/
#define AM335X_PADCTL_SS	0x00000040	/* Slew control slow	*/
#define AM335X_PADCTL_SF	0x00000000	/* Slew control fast	*/

#define	am335x_padctl(addr,val)	(*((uint32 *)(addr))) = (val)

#define AM335X_CONTROL_BASE   0x44E10000
#define AM335X_MAC_ID0_LO_OFF 0x630
#define AM335X_MAC_ID0_HI_OFF 0x634
#define AM335X_MAC_ID1_LO_OFF 0x638
#define AM335X_MAC_ID1_HI_OFF 0x63C
