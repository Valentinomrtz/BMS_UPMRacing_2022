/*
 *  Error Verification header
 *  Application layer
 */

#ifndef ERROR_VERIFICATION_H
#define	ERROR_VERIFICATION_H

void error_verification(bms*);
void error_input_comm(bms*);
void error_hv_monitoring(bms*);
void error_hv_limits(bms*);
void error_vcell_limits(bms*);
void error_vcell_diff(bms*);
void error_vstack_sum(bms*);
void error_vbatt_sum(bms*);
void error_tcell_limits(bms*);
void error_tcell_diff(bms*);
void error_current_limits(bms*);
void error_ow_cells(bms*);
void error_check_0(bms*);
void error_check_1(bms*);
void error_check_2(bms*);
#endif	/* ERROR_VERIFICATION_H */

