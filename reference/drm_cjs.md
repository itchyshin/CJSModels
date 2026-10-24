# Fit a first-capture-conditional CJS model

Fit a first-capture-conditional CJS model

## Usage

``` r
drm_cjs(
  data,
  phi = ~1,
  p = ~1,
  phi_data = NULL,
  p_data = NULL,
  selection = NULL,
  sd_phi = NULL,
  sd_p = NULL,
  terminal_constraint = NULL,
  control = list(),
  contrasts = list(phi = NULL, p = NULL),
  engine = c("tmb", "julia")
)
```

## Arguments

- data:

  A `cmr_data` object.

- phi:

  Survival formula, with logit unit-time apparent survival. M3 accepts
  at most one shared random intercept, such as `(1 | site)`.

- p:

  Detection formula, with logit detection conditional on alive. M3
  accepts at most one shared random intercept, such as `(1 | site)`.

- phi_data:

  Optional interval predictor table keyed by `id`, `interval_start`, and
  `interval_end`.

- p_data:

  Optional detection predictor table keyed by `id` and `occasion`.

- selection:

  Optional
  `list(eligibility = occasion_indices, assumption = "alive_available")`.
  Conditions each individual's likelihood on first capture at the
  realized occasion under an alive-and-available reference cohort.
  Shared-effect selection is unsupported.

- sd_phi, sd_p:

  Optional one-sided formulas for log SD of the persistent individual
  survival or detection effect. Predictors must be constant within
  individual.

- terminal_constraint:

  Optional named list fixing exactly one common final-process
  probability, for example `list(phi = 0.8)` (unit-time survival) or
  `list(p = 0.4)` (final-occasion detection). Values must be strictly
  between zero and one. It applies at the final declared interval or
  occasion, not at each individual's administrative endpoint.

- control:

  Options passed to
  [`stats::nlminb()`](https://rdrr.io/r/stats/nlminb.html).

- contrasts:

  Optional named list of process-specific contrast specifications,
  `list(phi = ..., p = ...)`. The fitted coding is retained for
  prediction and bootstrap refits.

- engine:

  Computational engine: native TMB or native CJSModels.jl. The Julia
  bridge currently admits fixed-effects CJS only.

## Value

A `drm_cjs` fit containing the optimizer and TMB objective.
Individual-effect fits also report quadrature refinement status and an
`order_timings` table with setup/optimization time, optimizer status,
iterations, and function and gradient evaluation counts. These timings
describe the fit that ran; they do not establish parameter recovery or
inference calibration.

## Examples

``` r
y <- rbind(c(1,0,0), c(1,0,1), c(1,1,0), c(1,1,1))
d <- cmr_data(y, frequency = c(20, 10, 10, 10))
fit <- drm_cjs(d)
coef(fit)
```
