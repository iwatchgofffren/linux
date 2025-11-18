/* // SPDX-License-Identifier: GPL-2.0-or-later
 * Wacom protocol 4 serial tablet driver
 *
 * Copyright 2025 Siarhei Arlouski <sa-kdev1@yandex.by>
 *
 * Many thanks to Vojtech Pavlik.
 * 
 *
 * This driver was developed from reverse-engineering official XP-Pad software
 * driver for windows.
 * ref: https://www.xp-pen.com/download/star-06c.html
 *
 * To do:
 *  Implement device registration - not done;
 *
 */
#include "linux/stddef.h"
#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/usb/input.h>
#include <linux/usb/quirks.h>

MODULE_AUTHOR("Siarhei Arlouski <sa-kdev1@yandex.by>");
MODULE_DESCRIPTION("Xp-Pen generic driver");
MODULE_LICENSE("GPL");

/* Connection for tablet */
#define XPTABLETCONN_WIRED 1
#define XPTABLETCONN_BLUETOOTH 2
#define XPTABLET_CONN_ANY 3

#define XPSURFACE_PLAIN 0
#define XPSURFACE_DISPLAY 1

#define XPSTYLUS_EMR 0

#define XPSTYL_ERASER_NO 0
#define XPSTYL_ERASER_YES 1

static const struct xppen_device_misc {
	u8 idproduct;
	char *name;
	u8 conntype;
} xppen_device_misc[] = {};

static const struct xppen_stylus {
	char *name;
	u8 stylustype; // EMR,
	u8 eraser;
} xppen_stylus[] = {
	// Keep this list sorted;
	{ "XpPen P05", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen X3ProRollerStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen X3ProSmartChipStylus", XPSTYLUS_EMR, XPSTYL_ERASER_YES },
	{ "XpPen X4SmartChipStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen X3EliteStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen X3ElitePlusStylus", XPSTYLUS_EMR, XPSTYL_ERASER_YES },
	{ "XpPen PA6", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen PA5", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P05D", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen PH2", XPSTYLUS_EMR, XPSTYL_ERASER_YES },
	{ "XpPen PH3BatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen PA2", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen PA1", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P5RBatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P06BatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_YES },
	{ "XpPen P2SBatteryStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P03SBatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P03BatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen P01BatteryFreeStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
	{ "XpPen p02BatteryStylus", XPSTYLUS_EMR, XPSTYL_ERASER_NO },
};

static const struct xppen_device {
	u16 idVendor;
	u8 idProduct;
	char *name;
	u8 conntype; /*bluetooth or usb*/
	u16 surfacetype; /*plain surface or drawing display*/
	const struct xppen_stylus *stype;
	const struct xppen_device_misc *mdev;
} xppen_device[] = {
	/* Keep this list sorted, please */
	{ 0x28bd, 0, "XpPen Star 06C", 0, 0, &xppen_stylus[0], NULL },

};
