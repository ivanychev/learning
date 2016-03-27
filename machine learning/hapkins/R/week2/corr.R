if(!exists("get_names", mode="function"))
  source("names.R")

corr <- function(directory, treshold = 0) {
  names <- get_names(1:332, directory)
  corrs <- numeric()
  for (name in names) {
    cur <- read.csv(name)
    cur <- cur[!is.na(cur[, "sulfate"]) &
               !is.na(cur[, "nitrate"]) &
               !is.na(cur[, "Date"]), ]
    if (nrow(cur) <= treshold) {
      next
    }
    corrs <- append(corrs, cor(cur[, "sulfate"], cur[, "nitrate"]))
  }
  corrs
}
