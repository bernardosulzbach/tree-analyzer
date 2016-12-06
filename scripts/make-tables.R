#!/usr/bin/env Rscript

library(xtable)
options(xtable.floating=FALSE)
options(xtable.timestamp="")
options(xtable.include.rownames=FALSE)

bakeResults <- function(filename, prefix="") {
    data <- read.csv(file=filename, sep=",", head=TRUE)

    bakeColumns <- function(BSTIndex, AVLIndex) {
        table <- data[, c(1, BSTIndex, AVLIndex)]

        label <- names(data[BSTIndex])
        label <- gsub("BST\\.", "", label)
        label <- gsub("\\.", " ", label)
        texName <- tolower(paste(prefix, gsub(" ", "-", label), ".tex", sep=""))

        # Add the time unit if needed.
        label <- gsub("(Insertion|Query|Removal) ", "", label)
        if (label == "Duration") {
            label <- paste(label, " (ms)")
            # Also change zeros to NAs.
            table[table == 0] <- NA
        }
        # Wait after changing zero times to NAs to calculate factors.
        table <- data.frame(table, table[,2] / table[,3])
        # Nothing here is Inf, it should be NA.
        table[table == Inf] <- NA
        
        colnames(table)[2] <- paste("BST", label)
        colnames(table)[3] <- paste("AVL", label)
        colnames(table)[4] <- "Ratio"

        table[1] <- format(table[1], big.mark=",", scientific=FALSE)
        table[2] <- format(table[2], big.mark=",", scientific=FALSE)
        table[3] <- format(table[3], big.mark=",", scientific=FALSE)

        xtab <- xtable(table, latex.environments = "center")
        display(xtab) <- c('d', 'd', 's', 's', 'f')
        align(xtab) <- "rrrrr"
        print(xtab, file=texName, tabular.environment="tabularx", width="\\textwidth")
    }

    for (i in c(2, 3, 4, 5, 10, 11, 12, 13, 18, 19, 20, 21)) {
        bakeColumns(i, i + 4)
    }
}

bakeResults("result.txt.csv")
bakeResults("result.txt.sorted.csv", "sorted-")
