/**
 * @file
 *
 * @date 04.02.2009
 * @author Eldar Abusalimov
 */

#include <drivers/vtparse_table.h>

#define TRANSITION(vt_action, vtparse_state) \
	((VT_ACTION_ ## vt_action) | ((VTPARSE_STATE_ ## vtparse_state) << 4))

__extension__ const state_change_t STATE_TABLE[15][256] = {
	[VTPARSE_STATE_ANYWHERE] = {
		[0x18         ] = TRANSITION(EXECUTE, GROUND),
		[0x1a         ] = TRANSITION(EXECUTE, GROUND),
		[0x80 ... 0x8f] = TRANSITION(EXECUTE, GROUND),
		[0x91 ... 0x97] = TRANSITION(EXECUTE, GROUND),
		[0x99         ] = TRANSITION(EXECUTE, GROUND),
		[0x9a         ] = TRANSITION(EXECUTE, GROUND),
		[0x9c         ] = TRANSITION(EXECUTE, GROUND),
		[0x1b         ] = TRANSITION(NONE, ESCAPE),
		[0x98         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
		[0x9e         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
		[0x9f         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
		[0x90         ] = TRANSITION(NONE, DCS_ENTRY),
		[0x9d         ] = TRANSITION(NONE, OSC_STRING),
		[0x9b         ] = TRANSITION(NONE, CSI_ENTRY),
	},
	[VTPARSE_STATE_CSI_ENTRY] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, CSI_INTERMEDIATE),
		[0x3a         ] = TRANSITION(NONE, CSI_IGNORE),
		[0x30 ... 0x39] = TRANSITION(PARAM, CSI_PARAM),
		[0x3b         ] = TRANSITION(PARAM, CSI_PARAM),
		[0x3c ... 0x3f] = TRANSITION(COLLECT, CSI_PARAM),
		[0x40 ... 0x7e] = TRANSITION(CSI_DISPATCH,GROUND),
	},
	[VTPARSE_STATE_CSI_IGNORE] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x20 ... 0x3f] = TRANSITION(IGNORE , ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE , ANYWHERE),
		[0x40 ... 0x7e] = TRANSITION(NONE, GROUND),
	},
	[VTPARSE_STATE_CSI_INTERMEDIATE] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x30 ... 0x3f] = TRANSITION(NONE, CSI_IGNORE),
		[0x40 ... 0x7e] = TRANSITION(CSI_DISPATCH, GROUND),
	},
	[VTPARSE_STATE_CSI_PARAM] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x30 ... 0x39] = TRANSITION(PARAM, ANYWHERE),
		[0x3b         ] = TRANSITION(PARAM, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x3a         ] = TRANSITION(NONE, CSI_IGNORE),
		[0x3c ... 0x3f] = TRANSITION(NONE, CSI_IGNORE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, CSI_INTERMEDIATE),
		[0x40 ... 0x7e] = TRANSITION(CSI_DISPATCH, GROUND),
	},
	[VTPARSE_STATE_DCS_ENTRY] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x3a         ] = TRANSITION(NONE, DCS_IGNORE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, DCS_INTERMEDIATE),
		[0x30 ... 0x39] = TRANSITION(PARAM, DCS_PARAM),
		[0x3b         ] = TRANSITION(PARAM, DCS_PARAM),
		[0x3c ... 0x3f] = TRANSITION(COLLECT, DCS_PARAM),
		[0x40 ... 0x7e] = TRANSITION(NONE, DCS_PASSTHROUGH),
	},
	[VTPARSE_STATE_DCS_IGNORE] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x7f] = TRANSITION(IGNORE, ANYWHERE),
		[0x9c         ] = TRANSITION(NONE, GROUND),
	},
	[VTPARSE_STATE_DCS_INTERMEDIATE] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x30 ... 0x3f] = TRANSITION(NONE, DCS_IGNORE),
		[0x40 ... 0x7e] = TRANSITION(NONE, DCS_PASSTHROUGH),
	},
	[VTPARSE_STATE_DCS_PARAM] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x30 ... 0x39] = TRANSITION(PARAM, ANYWHERE),
		[0x3b         ] = TRANSITION(PARAM, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x3a         ] = TRANSITION(NONE, DCS_IGNORE),
		[0x3c ... 0x3f] = TRANSITION(NONE, DCS_IGNORE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, DCS_INTERMEDIATE),
		[0x40 ... 0x7e] = TRANSITION(NONE, DCS_PASSTHROUGH),
	},
	[VTPARSE_STATE_DCS_PASSTHROUGH] = {
		[0x00 ... 0x17] = TRANSITION(PUT, ANYWHERE),
		[0x19         ] = TRANSITION(PUT, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(PUT, ANYWHERE),
		[0x20 ... 0x7e] = TRANSITION(PUT, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x9c         ] = TRANSITION(NONE, GROUND),
	},
	[VTPARSE_STATE_ESCAPE] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, ESCAPE_INTERMEDIATE),
		[0x30 ... 0x4f] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x51 ... 0x57] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x59         ] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x5a         ] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x5c         ] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x60 ... 0x7e] = TRANSITION(ESC_DISPATCH, GROUND),
		[0x5b         ] = TRANSITION(NONE, CSI_ENTRY),
		[0x5d         ] = TRANSITION(NONE, OSC_STRING),
		[0x50         ] = TRANSITION(NONE, DCS_ENTRY),
		[0x58         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
		[0x5e         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
		[0x5f         ] = TRANSITION(NONE, SOS_PM_APC_STRING),
// /*127*/ TRANSITION(EXECUTE, ANYWHERE), /* TODO -- Eldar*/
	},
	[VTPARSE_STATE_ESCAPE_INTERMEDIATE] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x20 ... 0x2f] = TRANSITION(COLLECT, ANYWHERE),
		[0x7f         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x30 ... 0x7e] = TRANSITION(ESC_DISPATCH, GROUND),
	},
	[VTPARSE_STATE_GROUND] = {
		[0x00 ... 0x17] = TRANSITION(EXECUTE, ANYWHERE),
		[0x19         ] = TRANSITION(EXECUTE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x20 ... 0x7f] = TRANSITION(PRINT, ANYWHERE),
		[0x80 ... 0x8f] = TRANSITION(EXECUTE, ANYWHERE),
		[0x91 ... 0x9a] = TRANSITION(EXECUTE, ANYWHERE),
		[0x9c         ] = TRANSITION(EXECUTE, ANYWHERE),
// /*127*/ TRANSITION(EXECUTE, ANYWHERE), /* TODO -- Eldar*/
	},
	[VTPARSE_STATE_OSC_STRING] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x7f] = TRANSITION(OSC_PUT, ANYWHERE),
		[0x9c         ] = TRANSITION(NONE, GROUND),
	},
	[VTPARSE_STATE_SOS_PM_APC_STRING] = {
		[0x00 ... 0x17] = TRANSITION(IGNORE, ANYWHERE),
		[0x19         ] = TRANSITION(IGNORE, ANYWHERE),
		[0x1c ... 0x1f] = TRANSITION(IGNORE, ANYWHERE),
		[0x20 ... 0x7f] = TRANSITION(IGNORE, ANYWHERE),
		[0x9c         ] = TRANSITION(NONE, GROUND),
	},
};

const VT_ACTION ENTRY_ACTIONS[] = {
	0 /* none for ANYWHERE */,
	VT_ACTION_CLEAR, /* CSI_ENTRY */
	0 /* none for CSI_IGNORE */,
	0 /* none for CSI_INTERMEDIATE */,
	0 /* none for CSI_PARAM */,
	VT_ACTION_CLEAR, /* DCS_ENTRY */
	0 /* none for DCS_IGNORE */,
	0 /* none for DCS_INTERMEDIATE */,
	0 /* none for DCS_PARAM */,
	VT_ACTION_HOOK, /* DCS_PASSTHROUGH */
	VT_ACTION_CLEAR, /* ESCAPE */
	0 /* none for ESCAPE_INTERMEDIATE */,
	0 /* none for GROUND */,
	VT_ACTION_OSC_START, /* OSC_STRING */
	0 /* none for SOS_PM_APC_STRING */,
};

const VT_ACTION EXIT_ACTIONS[] = {
	0 /* none for ANYWHERE */,
	0 /* none for CSI_ENTRY */,
	0 /* none for CSI_IGNORE */,
	0 /* none for CSI_INTERMEDIATE */,
	0 /* none for CSI_PARAM */,
	0 /* none for DCS_ENTRY */,
	0 /* none for DCS_IGNORE */,
	0 /* none for DCS_INTERMEDIATE */,
	0 /* none for DCS_PARAM */,
	VT_ACTION_UNHOOK, /* DCS_PASSTHROUGH */
	0 /* none for ESCAPE */,
	0 /* none for ESCAPE_INTERMEDIATE */,
	0 /* none for GROUND */,
	VT_ACTION_OSC_END, /* OSC_STRING */
	0 /* none for SOS_PM_APC_STRING */,
};

