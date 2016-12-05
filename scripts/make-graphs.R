#!/usr/bin/env Rscript

pngW <- 1200
pngH <- 500

verticals <- function(values) {
    sections <- 4
    ticks <- 10
    lines <- c()
    top <- ceiling(log(max(values)))
    for (i in seq(1, sections)) {
        a <- (i - 1) * top / 4
        b <- i * top / 4
        lines <- c(lines, seq(exp(a), exp(b), length.out=ticks))
    }
    log(lines)
}

plotResults <- function(filename, prefix="") {
    data <- read.csv(file=filename, sep=",", head=TRUE)

    # X is the same for all plots, just the element count.
    xLab <- "Elements"  # Better than the "ID" we are exporting.
    x <- data[, 1]
    lx <- log10(x)

    plotColumns <- function(yBSTIndex, yAVLIndex) {
        yRawLab <- names(data[yBSTIndex])
        yLab <- gsub("BST\\.", "", yRawLab)
        yLab <- gsub("\\.", " ", yLab)
        pngName <- tolower(paste(prefix, gsub(" ", "-", yLab), ".png", sep=""))

        # Add the time unit if needed.
        if (gsub("(Insertion|Query|Removal) ", "", yLab) == "Duration") {
            yLab <- paste(yLab, " (ms)")
        }
        yBST <- data[, yBSTIndex]
        lyBST <- log(yBST + 1)
        yAVL <- data[, yAVLIndex]
        lyAVL <- log(yAVL + 1)
        yCombined <- c(yBST, yAVL)
        lyCombined <- log(yCombined + 1)
        png(pngName, width=pngW, height=pngH)

        plot(lx, lyBST, pch=19, col="darkgreen", xaxt="n", xlab=xLab, yaxt="n", ylab=yLab)
        # Having lines would be a nice thing, but it is not necessary.
        # panel.first=abline(v=NULL, h=verticals(yCombined), lty=3, col="black")
        points(lx, lyAVL, pch=19, col="purple")
        axis(side=1, at=lx, labels=x)
        axis(side=2, at=lyCombined, labels=yCombined)
        # grid(nx=NULL, ny=NULL, log="y", col="gray", lty="dotted", lwd=par("lwd"), equilogs=TRUE)

        dev.off();
    }

    for (i in c(2, 3, 6, 7, 10, 11)) {
        plotColumns(i, i + 2)
    }
}

plotResults("result.txt.csv")
plotResults("result.txt.sorted.csv", "sorted-")
