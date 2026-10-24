#' Connect the optional standalone Julia twin
#' @param path Path to a Julia environment containing CJSModels and RCall. Defaults to
#'   `CJS_JL_PATH`; when unset, uses the active Julia environment.
#' @return Invisibly returns TRUE after loading the Julia module.
#' @export
#' @examples
#' \dontrun{cjs_julia_setup(Sys.getenv("CJS_JL_PATH"))}
cjs_julia_setup <- function(path = Sys.getenv("CJS_JL_PATH", "")) {
  if (!requireNamespace("JuliaCall", quietly = TRUE))
    stop("Install JuliaCall to use the optional Julia engine.", call. = FALSE)
  if (nzchar(path)) {
    path <- normalizePath(path, mustWork = TRUE)
    # Select dependencies before JuliaCall loads RCall. Activating afterwards
    # can mix incompatible dependency versions in the embedded Julia session.
    Sys.setenv(JULIA_PROJECT = path)
  }
  JuliaCall::julia_setup(installJulia = FALSE)
  JuliaCall::julia_command("using CJSModels")
  invisible(TRUE)
}
