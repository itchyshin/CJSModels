# First-capture-conditional capture-recapture

[`drm_cjs()`](https://itchyshin.github.io/CJSModels/reference/drm_cjs.md)
fits a fixed-effects Cormack–Jolly–Seber model conditional on each
animal’s first capture. The survival formula models logit unit-time
apparent survival. Over an interval of length $`\Delta`$, survival is
$`\phi_{\mathrm{unit}}^{\Delta}`$; the detection formula models
detection conditional on being alive and surveyed. This route does not
estimate abundance or unseen animals.

Apparent survival combines mortality and permanent emigration; this
model cannot separate them. The contract also excludes all-zero
histories, unknown entry, recruitment, tag loss, temporary emigration,
and behavioural trap dependence. A history whose first capture is its
final observation contributes likelihood one because it has no
post-capture information.

## Fit a model

\
`y`` ``<-`` `[`rbind`](https://rdrr.io/r/base/cbind.html)`(`\
`  `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``0``, ``0``, ``0``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``0``, ``1``, ``0``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``1``, ``0``, ``0``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``1``, ``1``, ``0``)``,`\
`  `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``0``, ``0``, ``1``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``0``, ``1``, ``1``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``1``, ``0``, ``1``)``, `[`c`](https://rdrr.io/r/base/c.html)`(``1``, ``1``, ``1``, ``1``)`\
`)`\
`d`` ``<-`` `[`cmr_data`](https://itchyshin.github.io/CJSModels/reference/cmr_data.md)`(``y``, id ``=`` `[`seq_len`](https://rdrr.io/r/base/seq.html)`(`[`nrow`](https://rdrr.io/r/base/nrow.html)`(``y``)``)``, occasions ``=`` ``1``:``4``, units ``=`` ``"years"``,`\
`              frequency ``=`` `[`c`](https://rdrr.io/r/base/c.html)`(``12``, ``4``, ``8``, ``4``, ``4``, ``4``, ``4``, ``4``)``)`\
`fit`` ``<-`` `[`drm_cjs`](https://itchyshin.github.io/CJSModels/reference/drm_cjs.md)`(``d``, phi ``=`` ``~``1``, p ``=`` ``~``1``)`\
[`coef`](https://rdrr.io/r/stats/coef.html)`(``fit``)`\
`#> phi:(Intercept)   p:(Intercept) `\
`#>      1.99417454      0.02522045`

## Predict and simulate conditionally

Training predictions return only keyed interval and occasion rows that
contribute to the objective.

\
`pred`` ``<-`` `[`predict`](https://rdrr.io/r/stats/predict.html)`(``fit``)`\
[`head`](https://rdrr.io/r/utils/head.html)`(``pred``$``phi``[`[`c`](https://rdrr.io/r/base/c.html)`(``"id"``, ``"interval_start"``, ``"phi_unit"``, ``"phi_interval"``)``]``)`\
`#>   id interval_start  phi_unit phi_interval`\
`#> 1  1              1 0.8801841    0.8801841`\
`#> 2  1              2 0.8801841    0.8801841`\
`#> 3  1              3 0.8801841    0.8801841`\
`#> 4  2              1 0.8801841    0.8801841`\
`#> 5  2              2 0.8801841    0.8801841`\
`#> 6  2              3 0.8801841    0.8801841`\
[`head`](https://rdrr.io/r/utils/head.html)`(``pred``$``p``)`\
`#>   id occasion         p`\
`#> 2  1        2 0.5063048`\
`#> 3  1        3 0.5063048`\
`#> 4  1        4 0.5063048`\
`#> 6  2        2 0.5063048`\
`#> 7  2        3 0.5063048`\
`#> 8  2        4 0.5063048`

Simulation retains the observed first-capture times, survey masks, and
administrative endpoints. It conditions on the first-capture emission
and keeps death absorbing. Supplying a seed gives reproducible data
without changing the caller’s random-number stream.

\
`simulated`` ``<-`` `[`simulate`](https://rdrr.io/r/stats/simulate.html)`(`\
`  ``fit``, nsim ``=`` ``1L``, seed ``=`` ``20261006`\
`)``[[``1L``]``]`\
`refit`` ``<-`` `[`drm_cjs`](https://itchyshin.github.io/CJSModels/reference/drm_cjs.md)`(`\
`  ``simulated``$``data``, phi ``=`` ``~``1``, p ``=`` ``~``1``,`\
`  phi_data ``=`` ``simulated``$``phi_data``, p_data ``=`` ``simulated``$``p_data`\
`)`\
[`coef`](https://rdrr.io/r/stats/coef.html)`(``refit``)`\
`#> phi:(Intercept)   p:(Intercept) `\
`#>       1.9745620      -0.2422642`

## Inspect fixed-effect intervals

Wald and profile intervals use the CJS-specific observed likelihood
curvature and constrained CJS refits, respectively. The parametric
bootstrap retains every attempt and its status when the original fit
passes admission; an ineligible original fit can be rejected before an
interval result is returned. Returned results expose a status for each
coefficient. These methods have not passed repeated-sample
interval-availability or coverage qualification. The current checks
report only target-specific single-fit endpoint capability and status;
repeated-sample availability and calibration remain open. An available
interval does not establish nominal calibration.

\
`ci`` ``<-`` `[`confint`](https://rdrr.io/r/stats/confint.html)`(``fit``, method ``=`` ``"wald"``)`\
[`attr`](https://rdrr.io/r/base/attr.html)`(``ci``, ``"target_status"``)`\
`#> phi:(Intercept)   p:(Intercept) `\
`#>            "ok"            "ok"`

## Scope

This example covers fixed effects only. Shared, individual, SD and
selection routes remain experimental; extraction-specific combinations
and scientific recovery/coverage checks are not established by this
article.
