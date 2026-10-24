# Predict process-specific quantities from a conditional CJS fit

Predict process-specific quantities from a conditional CJS fit

## Usage

``` r
# S3 method for class 'drm_cjs'
predict(
  object,
  newdata = NULL,
  type = c("response", "link"),
  target = NULL,
  ...
)
```

## Arguments

- object:

  A `drm_cjs` fit.

- newdata:

  `NULL` for contributing training rows, or a list with `phi`, `p`, and
  `units` keyed data frames. For integrated prediction from a
  reference-selection fit, include `selection`: a list with `first`
  (columns `id`, `first_index`, and `eligibility_index`), `phi` (all
  pre-capture intervals), and `p` (all pre-capture occasions plus
  logical `observed` and binary `capture` columns). Occasion indices are
  1-based positions in the fitted schedule; prehistory predictors must
  use the fitted schemas.

- type:

  Return link-scale linear predictors or response-scale probabilities.

- target:

  For individual-effect fits, `"zero_effect"` predicts at a zero random
  effect; `"integrated"` averages probabilities over the fitted
  marked-cohort reference mixing law, using fitted predictor-dependent
  SDs when present. For reference-selection fits, integrated prediction
  is conditioned on the supplied first-capture event. New profiles must
  include complete prehistory in `newdata$selection`. Integrated
  prediction is response-scale only and reports process averages at the
  supplied profiles.

- ...:

  Unused.

## Value

A list containing keyed `phi` and `p` data frames.
