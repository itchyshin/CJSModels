# Wald, profile, or parametric-bootstrap intervals for a conditional CJS fit

Wald, profile, or parametric-bootstrap intervals for a conditional CJS
fit

## Usage

``` r
# S3 method for class 'drm_cjs'
confint(
  object,
  parm,
  level = 0.95,
  method = c("wald", "profile", "bootstrap"),
  nsim = 200L,
  seed = NULL,
  min_usable = 100L,
  ...
)
```

## Arguments

- object:

  A `drm_cjs` fit.

- parm:

  Optional coefficient names or indices. For constant individual or
  shared SD profiles, use `"sd:phi"` or `"sd:p"`. For an individual or
  shared SD formula, use a fitted coefficient name such as `"sd_phi:z"`
  or `"sd_p:z"`.

- level:

  Confidence level.

- method:

  `"wald"`, `"profile"`, or `"bootstrap"`.

- nsim:

  Bootstrap attempts.

- seed:

  Optional bootstrap seed.

- min_usable:

  Minimum usable bootstrap fits before percentile intervals are
  returned.

- ...:

  Unused.

## Value

An interval matrix with method diagnostics in attributes. The bootstrap
`attempts` attribute retains convergence, quadrature, curvature, and
numerical zero-SD diagnostics separately. Profile and
parametric-bootstrap intervals are available for native integrated
individual-effect fits. Wald intervals additionally require nonsingular
interior curvature. Bootstrap eligibility is recorded separately from
Wald curvature and requires finite converged estimates with accepted
quadrature refinement for integrated fits. Bootstrap intervals require
at least `min_usable` refits; availability does not establish
calibration. Constant shared SD limits exponentiate finite interior
log-SD profile endpoints and do not evaluate an exact-zero model.
Shared-effect fixed-coefficient and SD-formula profile intervals require
a stationary positive-curvature latent mode; shared-effect Wald and
bootstrap intervals remain unavailable. Fixed-effect rows are on the
coefficient scale. Ordinary individual coefficient profiles require
refined fitted integration, rebuild and refine each constrained point
over the saved quadrature ladder, and withhold limits when the refitted
center disagrees with or improves on the fitted likelihood, any
constrained point improves on the fitted likelihood, or an endpoint
fails its numerical check. If any constrained point improves on the fit,
both endpoint limits are withheld. Availability does not establish
calibration. Individual `sd:phi` and `sd:p` profile rows are on the SD
scale. Their exact-zero endpoint is evaluated with the selected effect
removed and the remaining CJS model reoptimized. A constrained endpoint
is withheld when its optimizer fails or quadrature does not refine.
SD-formula coefficients can also be profiled by their `sd_phi:<column>`
or `sd_p:<column>` names for individual or shared effects; shared
profile points re-solve the latent mode. Those limits use the log-SD
coefficient scale. Profile availability does not establish calibration.
