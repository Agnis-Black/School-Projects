# Part 1

Jet1 <- read.csv("D:/Dataset_ExpressJet.csv")
categoriesJet <- Jet1$Delayed
Jet2 <- read.csv("D:/Dataset_UnitedUS.csv")
categoriesUS <- Jet2$Delayed

# Part 2 Dataset for ExpressJet

# (a)

hist(categoriesJet,
     right = FALSE, # To get left closed interval and right open
     breaks = c(0,50,100,150,200,250),
     ylim = c(0,120) )

# (b)

# The histogram is right skewed and not symmetric.
# It is unimodal.

# (c)

TI_Q1_Q3 <- function(x){
  n <- length(x)
  if(n %% 2 == 1){Q <- fivenum(x[-(n+1)/2])[c(2,4)]}
  if(n %% 2 == 0){Q <- fivenum(x)[c(2,4)]}
  result <- as.data.frame(list(Q1 = Q[1], Q3 = Q[2]))
  return(result)
}

TI_Q1_Q3(categoriesJet)
# Q1 is 18 and Q3 is 66
min(categoriesJet)
# lowest value is 0
max(categoriesJet)
# Highest value is 218
mean(categoriesJet)
# mean is 47.62179 about 47.62

# 5 number summary is 0, 18, 47.62, 66, 218

# (d)

mean(categoriesJet) # mean is 47.622
sd(categoriesJet) # sd is 42.947
length(categoriesJet) # size is 156

# (e)

# Yes, Sample size is considered big enough because it is greater
# than 30.

# Part 3 (a)

# significance level is 0.076
a <- 0.076

# mu1 is average number of delayed flights for US Airways
# mu2 is average number of delayed flights for ExpressJet

# (i)
# Null Hypothesis: mu1 - mu2 = 2
# Alternative Hypothesis: mu1 - mu2 > 2

# data not paired
# variance is unknown and assumed unequal.
# Use t

# Sample information

# AirwaysUS 
mean(categoriesUS) # mean is 58.469
sd(categoriesUS) # sd is 63.126
length(categoriesUS) # size is 130

# ExpressJet
# mean is 47.622
# sd is 42.947
# size is 156

# Confidence interval is 0.924

# (ii)

t.test(categoriesUS,categoriesJet,
       mu = 2,
       alternative = "greater",
       paired = FALSE,
       conf.level = 0.924,
       var.equal = FALSE)

# (iii)

#         Welch Two Sample t-test
#    data:  categoriesUS and categoriesJet
#   t = 1.3575, df = 220.42, p-value = 0.088
# alternative hypothesis: true difference in means is greater than 2
#   92.4 percent confidence interval:
#      1.47885     Inf
#      sample estimates:
#      mean of x mean of y 
#      58.46923  47.62179 

# (iv)

# degree of freedom formula
# v_num = ( (s1^2) / n1 + (s2^2) / n2)^2
# v_den = ( ((s1^2) / n1)^2 / (n1 - 1) + ((s2^2) / n2)^2 / (n2 - 1))
# degree of freedom is 220.42, rounded down to 220

# Test Statistic Formula
# t_num = (mu1 - mu2) - d0
# t_den = sqrt( ( (s1^2) / n1) + ( (s2^2) / n2) )
# Test Statistic is 1.3575 about 1.358

# (v)

# Critical value 
qt(1 - a, 220) # critical value is 1.437489 about 1.437

# (vi)

# Critical region to reject H0 is t > 1.437

# (viii)

# Formula on R:

# finding p-value, P(T > 1.358)
pt(1.358, df = 220, lower.tail = FALSE)
# p value is 0.08792739 about 0.08793

# formula on calculator = tcdf(1.358,999,220)

# p-value from result p = 0.088

# (vii) and (xi)

# Decisions
# Using critical region: Since 1.358 is smaller than 1.437, 
# we do not reject H0
# Using p-value: Since our p-value is large, even larger than our cutoff
# value of 0.076, we do not reject H0

# (x)

# Conclusion (Reject alternate Hypothesis)
# There is not enough evidence that the average number of delayed flights
# from United/US Airways is higher than the average number of delayed
# flights from ExpressJets by more than 2 flights.

# Part 3 (b)

# From R:
# 92.4 percent confidence interval:
#      1.47885     Inf

# A 92.4% Confidence Interval for mu1 - mu2 is : 
# 1.47885 < mu1 - mu2 < Infinity

# Formula:
# (x1 - x2) - t(a/2) * sqrt( (s1^2) / n1 + (s2^2) / n2) < mu1 - mu2 <
# (x1 - x2) + t(a/2) * sqrt( (s1^2) / n1 + (s2^2) / n2)

# parameter the confidence interval is for (1.47885,Inf)

# interpretation of confidence interval:
# Since both values of our confidence interval are positive,
# this indicates that, on the average, the mean number of delayed flights from
# US Airways is higher than the mean number of flights delayed from ExpressJets.