if(!exists("get_names", mode="function"))
  source("names.R")

complete <- function(directory, id = 1:332) {
  wd <- getwd()
  setwd(directory)
  names <- get_names(id)
  df <- data.frame(id=integer(), nobs=integer())
  for (i in 1:length(id)) {
    current <- read.csv(names[i])
    num <- sum(!is.na(current[, "sulfate"]) &
               !is.na(current[, "nitrate"]) &
               !is.na(current[, "Date"]))
    df <- rbind(c(id[i], num), df)
  }
  setwd(wd)
  names(df) <- c("id", "nobs")
  df
}
