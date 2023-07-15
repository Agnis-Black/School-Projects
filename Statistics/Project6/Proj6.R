# Project 6 Version 5

# (C1)

hurricane <- read.csv("D:/Hurricane.csv")
categories <- hurricane$Cat

# (C2)

# Histogram is right skewed
hist(categories,
     right = FALSE,
     breaks = c(1,2,3,4,5,6) )

# (C3)

table(categories)
# categories
# 1   2   3   4   5 
# 121  83  62  25   4
# category 5 has least hurricanes that made landfall
# category 1 has most hurricanes that made landfall

# (C4)

shapiro.test(categories)
# Shapiro-Wilk normality test
# data:  categories
# W = 0.83268, p-value < 2.2e-16
# population is not normally distributed because
# p value less than 0.05

# (C5)

mean(categories)
# 2.010169
var(categories)
# 1.08493
sd(categories)
# 1.0416

# (C6)

sampling_jp <- function(dataset, seed_value, num_samples, sizejp){
  samples1 <- matrix(NA, nrow = num_samples, ncol = sizejp)
  set.seed(seed_value)
  for(i in 1:num_samples){
    samples1[i,] <- sample(dataset, size = sizejp, replace = TRUE)
  }
  rowmeans1 <- rowMeans(samples1)
  graph <- hist(rowmeans1, right = FALSE, xlab = "Sample Means",
                main = "Histogram",
                sub = paste("Size = ", sizejp))
  sw <- shapiro.test(rowmeans1)
  result <- list(SampleMeans = rowmeans1, Shapiro = sw, Histogram = graph)
  return(result)
}


# (Q7) Number of samples is another way of saying the number of trials
# you have and the sample size is how many elements are in that trial.
# For example, you have 5 flavors of cookies with 10 in each batch.

# (Q8)
?sample
# It looks like an array of samples is being created in order inside a for loop.
# Random samples are created within specific parameters given.
# sample(x, size, replace = FALSE, prob = NULL)
# x could be a vector or a positive integer.
# n	is a positive number, the number of items to choose from. 
# size	is a non-negative integer giving the number of items to choose.
# replace is asking if sampling should be with a replacement?
# prob is a vector of probability weights for obtaining the elements 
# of the vector being sampled.

# (C9)

run1 <- sampling_jp(categories,250,130,17)
run1
# Shapiro-Wilk normality test
# data:  rowmeans1
# W = 0.95344, p-value = 0.0002102
# $Histogram
# $breaks
# [1] 1.4 1.6 1.8 2.0 2.2 2.4 2.6 2.8 3.0
# $counts
# [1]  7 26 41 36 10  7  2  1
# $density
# [1] 0.26923077 1.00000000 1.57692308 1.38461538 0.38461538
# [6] 0.26923077 0.07692308 0.03846154
# $mids
# [1] 1.5 1.7 1.9 2.1 2.3 2.5 2.7 2.9
# $xname
# [1] "rowmeans1"
# $equidist
# [1] TRUE
# attr(,"class")
# [1] "histogram"

# (C10)

run2 <- sampling_jp(categories,250,130,97)
run2
# Shapiro-Wilk normality test
# data:  rowmeans1
# W = 0.9955, p-value = 0.9583
# $Histogram
# $breaks
# [1] 1.75 1.80 1.85 1.90 1.95 2.00 2.05 2.10 2.15 2.20 2.25 2.30 2.35
# $counts
# [1]  4  5 10 18 19 19 26 12 11  4  1  1
# $density
# [1] 0.6153846 0.7692308 1.5384615 2.7692308 2.9230769 2.9230769 4.0000000 1.8461538 1.6923077 0.6153846 0.1538462 0.1538462
# $mids
# [1] 1.775 1.825 1.875 1.925 1.975 2.025 2.075 2.125 2.175 2.225 2.275 2.325
# $xname
# [1] "rowmeans1"
# $equidist
# [1] TRUE
# attr(,"class")
# [1] "histogram"

# (Q11) The p-value is 0.0002102 from Shapiro-wilk normality 
# test since p is smaller than 0.05 data is not 
# normally distributed. The histogram itself looks kinda bell-shaped
# but not completely symmetrical, it is more right skewed.

# (C12) The p-value is 0.9583 from Shapiro-wilk normality 
# test since p is larger than 0.05 data is normally distributed. 
# The histogram itself looks somewhere semi-uniform and semi-bellshaped.
# it is not skewed, it looks more symmetrical but not perfectly symmetrical.

# (Q13) Central limit theory states that when random
# samples mean is taken, the individual normalized sum
# can become normally distributed even if the individual samples are not
# normally distributed. Conditions are that trials have to large enough,
# approximately 30.Simply based on the sample size, I would say C9 Central
# Limit Theory does not hold because of sample size 17 and for C10 CLT does hold
# because of sample size being 97. Furthermore, according to Q11 C9 is not
# normally distributed and C10 is normally distributed. The shapes of the graphs
# also support my answer from Q11 and Q12.

# (Q14) E(X) for size 17
# E(X) = mean of sample = sum of mid*count
mu1 <- 7*(1.5)+26*(1.7)+41*(1.9)+36*(2.1)+10*(2.3)+7*(2.5)+2*(2.7)+1*(2.9)
mu1/130
# 1.976923

# E(x) for size 97, same formula as above
mu2 <- 4*1.775+1.825*5+1.875*10+1.925*18+1.975*19+
  2.025*19+2.075*26+2.125*12+2.175*11+2.225*4+2.275+2.325
mu2/130
# 2.019231

# (Q15)
# SD(X) = (sd of population) / sqrt(sample size)
mu1_squared <- 7*7*(1.5)+26*26*(1.7)+41*41*(1.9)+36*36*(2.1)+
  10*10*(2.3)+7*7*(2.5)+2*2*(2.7)+1*1*(2.9)
mu1_var <- mu1_squared - mu1*mu1
mu1_var # variance negative cannot proceed
# -65531.7
# formula upon continuing SD(X) = sqrt(mu1_var)/sqrt(17)

mu2_squared <- 4*4*1.775+1.825*5*5+1.875*10*10+1.925*18*18+
  1.975*19*19+2.025*19*19+2.075*26*26+2.125*12*12+
  2.175*11*11+2.225*4*4+2.275+2.325
mu2_var <- mu2_squared - mu2*mu2
mu2_var
# -64564.95
# cannot proceed
# formula upon continuing SD(X) = sqrt(mu2_var)/sqrt(97)

# (Q16)

mean(run1$SampleMeans) 
# 1.970588
mean(run2$SampleMeans)
# 2.01927

# (Q17)
 
sd(run1$SampleMeans)
# 0.2581521
sd(run2$SampleMeans) 
# 0.112782

# (Q18) Using means from Q14 and Q16 using more sample size does 
# improve accuracy of calculations as the mean for size 97 is much closer
# upon rough and table calculation.