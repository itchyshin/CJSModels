#include <TMB.hpp>
#include "cjs_kernel.h"
template<class Type>
Type objective_function<Type>::operator()() {
  DATA_INTEGER(model_type);
  // CJS histories have their own data and likelihood contract. Dispatch before
  // ordinary-response fields so CJS callers do not supply dummy legacy data.
  if (model_type == 1000) {
    DATA_INTEGER(cmr_N);
    DATA_INTEGER(cmr_T);
    DATA_IVECTOR(cmr_y);
    DATA_IVECTOR(cmr_observed);
    DATA_IVECTOR(cmr_first);
    DATA_IVECTOR(cmr_end);
    DATA_VECTOR(cmr_delta);
    DATA_IVECTOR(cmr_frequency);
    DATA_MATRIX(cmr_X_phi);
    DATA_MATRIX(cmr_X_p);
    DATA_VECTOR(cmr_offset_phi);
    DATA_VECTOR(cmr_offset_p);
    PARAMETER_VECTOR(beta_phi);
    PARAMETER_VECTOR(beta_p);
    vector<Type> eta_phi = cmr_X_phi * beta_phi + cmr_offset_phi;
    vector<Type> eta_p = cmr_X_p * beta_p + cmr_offset_p;
    return cjs_nll(cmr_y, cmr_observed, cmr_first, cmr_end,
                   cmr_delta, eta_phi, eta_p, cmr_frequency, cmr_N, cmr_T);
  }
  if (model_type == 1001) {
    DATA_INTEGER(cmr_N);
    DATA_INTEGER(cmr_T);
    DATA_IVECTOR(cmr_y);
    DATA_IVECTOR(cmr_observed);
    DATA_IVECTOR(cmr_first);
    DATA_IVECTOR(cmr_end);
    DATA_VECTOR(cmr_delta);
    DATA_IVECTOR(cmr_frequency);
    DATA_MATRIX(cmr_X_phi);
    DATA_MATRIX(cmr_X_p);
    DATA_VECTOR(cmr_offset_phi);
    DATA_VECTOR(cmr_offset_p);
    DATA_MATRIX(cmr_Z_phi);
    DATA_MATRIX(cmr_Z_p);
    PARAMETER_VECTOR(beta_phi);
    PARAMETER_VECTOR(beta_p);
    PARAMETER_VECTOR(u_phi);
    PARAMETER_VECTOR(u_p);
    PARAMETER(log_sigma_phi);
    PARAMETER(log_sigma_p);
    vector<Type> eta_phi = cmr_X_phi * beta_phi + cmr_offset_phi;
    vector<Type> eta_p = cmr_X_p * beta_p + cmr_offset_p;
    if (u_phi.size()) {
      vector<Type> b_phi = u_phi;
      b_phi *= exp(log_sigma_phi);
      eta_phi += cmr_Z_phi * b_phi;
    }
    if (u_p.size()) {
      vector<Type> b_p = u_p;
      b_p *= exp(log_sigma_p);
      eta_p += cmr_Z_p * b_p;
    }
    return cjs_shared_nll(cmr_y, cmr_observed, cmr_first, cmr_end,
                          cmr_delta, eta_phi, eta_p, cmr_frequency,
                          u_phi, u_p, cmr_N, cmr_T);
  }
  // Shared unit-specific SDs use the same standardized joint CJS target as
  // scalar mode 1001. No scale Jacobian is added to the normalized u prior.
  if (model_type == 1003) {
    DATA_INTEGER(cmr_N);
    DATA_INTEGER(cmr_T);
    DATA_IVECTOR(cmr_y);
    DATA_IVECTOR(cmr_observed);
    DATA_IVECTOR(cmr_first);
    DATA_IVECTOR(cmr_end);
    DATA_VECTOR(cmr_delta);
    DATA_IVECTOR(cmr_frequency);
    DATA_MATRIX(cmr_X_phi);
    DATA_MATRIX(cmr_X_p);
    DATA_VECTOR(cmr_offset_phi);
    DATA_VECTOR(cmr_offset_p);
    DATA_MATRIX(cmr_Z_phi);
    DATA_MATRIX(cmr_Z_p);
    DATA_MATRIX(cmr_sd_X_phi);
    DATA_MATRIX(cmr_sd_X_p);
    DATA_VECTOR(cmr_sd_offset_phi);
    DATA_VECTOR(cmr_sd_offset_p);
    PARAMETER_VECTOR(beta_phi);
    PARAMETER_VECTOR(beta_p);
    PARAMETER_VECTOR(u_phi);
    PARAMETER_VECTOR(u_p);
    PARAMETER_VECTOR(log_sd_phi);
    PARAMETER_VECTOR(log_sd_p);
    if (cmr_sd_X_phi.rows() != u_phi.size() || cmr_sd_X_p.rows() != u_p.size() ||
        cmr_sd_X_phi.cols() != log_sd_phi.size() || cmr_sd_X_p.cols() != log_sd_p.size() ||
        cmr_sd_offset_phi.size() != u_phi.size() || cmr_sd_offset_p.size() != u_p.size())
      error("CJS shared SD design dimensions do not match the latent units");
    vector<Type> eta_phi = cmr_X_phi * beta_phi + cmr_offset_phi;
    vector<Type> eta_p = cmr_X_p * beta_p + cmr_offset_p;
    if (u_phi.size()) {
      vector<Type> logs = cmr_sd_X_phi * log_sd_phi + cmr_sd_offset_phi;
      vector<Type> b = u_phi;
      for (int j=0; j<b.size(); ++j) {
        Type sd = exp(logs(j));
        if (!R_FINITE(asDouble(sd)) || asDouble(sd)<=0)
          error("CJS shared SD must be finite and strictly positive");
        b(j) *= sd;
      }
      eta_phi += cmr_Z_phi * b;
    }
    if (u_p.size()) {
      vector<Type> logs = cmr_sd_X_p * log_sd_p + cmr_sd_offset_p;
      vector<Type> b = u_p;
      for (int j=0; j<b.size(); ++j) {
        Type sd = exp(logs(j));
        if (!R_FINITE(asDouble(sd)) || asDouble(sd)<=0)
          error("CJS shared SD must be finite and strictly positive");
        b(j) *= sd;
      }
      eta_p += cmr_Z_p * b;
    }
    return cjs_shared_nll(cmr_y, cmr_observed, cmr_first, cmr_end,
                          cmr_delta, eta_phi, eta_p, cmr_frequency,
                          u_phi, u_p, cmr_N, cmr_T);
  }
  if (model_type == 1002) {
    DATA_INTEGER(cmr_N);
    DATA_INTEGER(cmr_T);
    DATA_IVECTOR(cmr_y);
    DATA_IVECTOR(cmr_observed);
    DATA_IVECTOR(cmr_first);
    DATA_IVECTOR(cmr_end);
    DATA_VECTOR(cmr_delta);
    DATA_IVECTOR(cmr_frequency);
    DATA_MATRIX(cmr_X_phi);
    DATA_MATRIX(cmr_X_p);
    DATA_MATRIX(cmr_sd_X_phi);
    DATA_MATRIX(cmr_sd_X_p);
    DATA_VECTOR(cmr_sd_offset_phi);
    DATA_VECTOR(cmr_sd_offset_p);
    DATA_INTEGER(cmr_selection);
    DATA_INTEGER(cmr_terminal_phi);
    DATA_INTEGER(cmr_terminal_p);
    DATA_IVECTOR(cmr_eligibility);
    DATA_VECTOR(cmr_offset_phi);
    DATA_VECTOR(cmr_offset_p);
    DATA_VECTOR(cmr_gh_nodes);
    DATA_VECTOR(cmr_gh_weights);
    DATA_INTEGER(cmr_has_individual_phi);
    DATA_INTEGER(cmr_has_individual_p);
    PARAMETER_VECTOR(beta_phi);
    PARAMETER_VECTOR(beta_p);
    PARAMETER_VECTOR(log_sd_phi);
    PARAMETER_VECTOR(log_sd_p);
    vector<Type> eta_phi = cmr_X_phi * beta_phi + cmr_offset_phi;
    vector<Type> eta_p = cmr_X_p * beta_p + cmr_offset_p;
    vector<Type> individual_log_sd_phi = cmr_sd_X_phi * log_sd_phi + cmr_sd_offset_phi;
    vector<Type> individual_log_sd_p = cmr_sd_X_p * log_sd_p + cmr_sd_offset_p;
    vector<Type> cmr_individual_loglik(cmr_N);
    vector<Type> cmr_selection_log_num(cmr_N);
    vector<Type> cmr_selection_log_den(cmr_N);
    Type nll = cjs_individual_nll(cmr_y, cmr_observed, cmr_first, cmr_end,
                                  cmr_delta, eta_phi, eta_p, cmr_frequency,
                                  cmr_gh_nodes, cmr_gh_weights,
                                  individual_log_sd_phi, individual_log_sd_p,
                                  cmr_eligibility, cmr_selection,
                                  cmr_has_individual_phi, cmr_has_individual_p,
                                  cmr_terminal_phi, cmr_terminal_p,
                                  cmr_N, cmr_T, cmr_individual_loglik,
                                  cmr_selection_log_num, cmr_selection_log_den);
    REPORT(cmr_individual_loglik);
    REPORT(cmr_selection_log_num);
    REPORT(cmr_selection_log_den);
    return nll;
  }
  error("Unsupported CJS model_type");
  return Type(0);
}
