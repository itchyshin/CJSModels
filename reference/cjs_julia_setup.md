# Connect the optional standalone Julia twin

Connect the optional standalone Julia twin

## Usage

``` r
cjs_julia_setup(path = Sys.getenv("CJS_JL_PATH", ""))
```

## Arguments

- path:

  Path to a Julia environment containing CJSModels and RCall. Defaults
  to `CJS_JL_PATH`; when unset, uses the active Julia environment.

## Value

Invisibly returns TRUE after loading the Julia module.

## Examples

``` r
if (FALSE) cjs_julia_setup(Sys.getenv("CJS_JL_PATH")) # \dontrun{}
```
