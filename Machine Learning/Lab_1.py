import numpy as np

np.random.seed(1)


#Problem 1

#Problem 1.1
def estimate(p, nSample):
  """
  Estimate the value of p by drawing samples with varying number of cast
  Input:
    - p:    a 1-D numpy array of size k (number of events), 
            encoding the probability of each of the k outcomes
    - nSample: a 1-D numpy array of size m specifying the sample sizes.
            Effectively, we run m number of experiments,
            with each experiment drawing nSample[j] number of samples (j=0,...,m-1)
  Outputs:
    - ProbEst: an m-by-k matrix (2-D numpy array), 
                whose j-th row (j >= 0) encodes the probability estimate 
                for the k events based on nSample[j] number of samples
  """  

  np.random.seed(1)
  k = p.size
  m = nSample.size
  ProbEst = np.empty([m, k], dtype=float)
  # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  # for n = nSample[0], nSample[1], ..., nSample[-1] (btw, -1 mean?)
  #    Throw the dice for n times by calling np.random.multinomial(n, p)
  #    Estimate p_1, ..., p_k and record it in a row of the ProbEst matrix
 
  # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  return ProbEst


#Problem 1.3
def estimate_efficient(p, nSample_start, nSample_end):
  """
  Estimate the value of p by drawing samples with varying number of nSample
  This function will call np.random.multinomial only once.

  Input:
  - p: a 1-D numpy array of size k (number of events), 
            encoding the probability of each of the k outcomes
  - nSample_start: an integer specifying the starting/minimum number of samples
  - nSample_end: an integer specifying the ending/maximum number of samples (inclusive)
    We require that nSample_end must be a multiple of nSample_start

  In the sense of section 1.1, the estimate function there will equivalently call
    nSample = np.arange(nSample_start, nSample_end+1, nSample_start)
    estimate(p, nSample)

  Outputs:
  - ProbEst: an m-by-k matrix (2-D numpy array), where m = nSample_end/nSample_start.
              The j-th (j >= 0) row encodes the probability estimate 
                for the k events based on nSample_start*(j+1) number of samples
  """

  assert(nSample_end % nSample_start == 0)

  np.random.seed(1)

  # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  

  # Some processing to aggregate the results
 

  # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  return ProbEst

#Problem 2

#Problme 2.1-step 1
def featureNormalization(X):
    """
    Normalize each feature for the input set
    Input:
    - X: a 2-D numpy array of shape (num_train, num_features)
    Outputs:
    - X_normalized: a 2-D numpy array of shape (num_train, num_features)
    - X_mean: a 1-D numpy array of length (num_features)
    - X_std: a 1-D numpy array of length (num_features)
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return X_normalized, X_mean, X_std

#Problme 2.1-step 2
def applyNormalization(X, X_mean, X_std):
    """
    Normalize each feature for the input set X
    Input:
    - X: a 2-D numpy array of shape (num_test, num_features)
    - X_mean: a 1-D numpy array of length (num_features)
    - X_std: a 1-D numpy array of length (num_features)

    Output:
    - X_normalized: a 2-D numpy array of shape (num_test, num_features)  
    """

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return X_normalized

#Problem 2.2
#Problem 2.2-step 1
def computeMSE(X, y, theta):
    """
    Compute MSE for the input set (X,y) with theta
    Inputs:
    - X: a 2-D numpy array of shape (num_samples, num_features+1)
    - y: a 1-D numpy array of length (num_samples)
    - theta: a 1-D numpy array of length (num_features+1)
    Output:
    - error: MSE, a real number
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
 

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return error

#Problem 2.2-step 2
def computeGradient(X, y, theta):
    """
    Compute the gradient of theta
    Inputs:
    - X: A 2-D numpy array of shape (num_train, num_features+1)
    - y: A 1-D numpy array of length (num_train)
    - theta: A 1-D numpy array of length (num_features+1)
    Output:
    - gradient: A 1-D numpy array of length (num_features+1)
    """

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
  

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return gradient


#Problem 2.2-step 3
def gradientDescent(X, y, theta, alpha, num_iters):
    """
    Update theta using equation (12) for num_iters times.
    Input: 
    - X: a numpy array of shape (num_train, num_features+1)
    - y: a numpy array of shape (num_train, 1)
    - theta: a 1-D numpy array of length (num_features+1)
    - alpha: learning rate, a scalar
    - num_iters: an integer specifying how many steps to run the gradient descent
    Outputs:
    - theta: the final theta, a 1-D numpy array of length (num_features+1). 
            You can directly overwrite the theta in the input argument, and return it.
    - Loss_record: a 1-D numpy array of length (num_iters), 
            recording the loss value of Eq (10) at every iteration, 
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
   

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return theta, Loss_record

#Problem 2.5-step 1
def closeForm(X, y):
    """
    Compute close form solution for theta
    Inputs:
    - X: a numpy array of shape (num_train, num_features+1)
    - y: a 1-D numpy array of length (num_train)
    Output:
    - theta: a 1-D numpy array of length (num_features+1)
    """
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
   

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return theta
