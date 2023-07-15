import numpy as np
np.random.seed(1)
#Problem 1

# Problem 1-step1
def my_euclidean_dist(X_test, X_train):
    """
    Compute the distance between each test example and each training example.

    Input:
    - X_test: A numpy array of shape (num_test, dim_feat) containing test data
    - X_train: A numpy array of shape (num_train, dim_feat) containing training data

    Output:
    - dists: A numpy array of shape (num_test, num_train) where 
            dist[i, j] is the Euclidean distance between the i-th test example 
            and the j-th training example
    """
    num_test = X_test.shape[0]
    num_train = X_train.shape[0]
    dists = np.zeros((num_test, num_train))
    # TODO:
    # Compute the L2 distance between all test and training examples.
    #
    # One most straightforward way is to use nested for loop
    # to iterate over all test and training samples.
    # Here is the pseudo-code:
    # for i = 0 ... num_test - 1
    #    a[i] = square of the norm of the i-th test example
    # for j = 0 ... num_train - 1
    #    b[j] = square of the norm of the j-th training example
    # for i = 0 ... num_test - 1
    #    for j = 0 ... num_train - 1
    #        dists[i, j] = a[i] + b[j] - 2 * np.dot(i-th test example, j-th training example)
    # return dists
    
    
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****


    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)***** 

    return dists

def euclidean_dist(X_test, X_train):
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    dists = np.add(np.sum(X_test ** 2, axis=1, keepdims=True), np.sum(X_train ** 2, axis=1, keepdims=True).T) - 2* X_test @ X_train.T
  
    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return dists

#Problem 1-step2
def find_k_neighbors(dists, Y_train, k):
    """
    find the labels of the top k nearest neighbors

    Inputs:
    - dists: distance matrix of shape (num_test, num_train)
    - Y_train: A numpy array of shape (num_train) containing ground true labels for training data
    - k: An integer, k nearest neighbors

    Output:
    - neighbors: A numpy array of shape (num_test, k), where each row containts the 
                labels of the k nearest neighbors for each test example
    """
    # TODO:
    # find the top k nearest neighbors for each test sample.
    # retrieve the corresponding labels of those neighbors.
    # Here is the pseudo-code:
    # for i = 0 ... num_test
    #     idx = numpy.argsort(i-th row of dists)
    #     neighbors[i] = Y_train(idx[0]), ..., Y_train(idx[k-1])
    # return neighbors
    # Advanced: You can accelerate the code by, e.g., argsort on the `dists` matrix directly

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return neighbors

#Problem 1-step3
def knn_predict(X_test, X_train, Y_train, k):
    """
    predict labels for test data.

    Inputs:
    - X_test: A numpy array of shape (num_test, dim_feat) containing test data.
    - X_train: A numpy array of shape (num_train, dim_feat) containing training data.
    - Y_train: A numpy array of shape (num_train) containing ground true labels for training data
    - k: An integer, k nearest neighbors

    Output:
    - Y_pred: A numpy array of shape (num_test). Predicted labels for the test data.
    """
    # TODO:
    # find the labels of k nearest neighbors for each test example,
    # and then find the majority label out of the k labels
    #
    # Here is the pseudo-code:
    # dists = euclidean_dist(X_test, X_train)
    # neighbors = find_k_neighbors(dists, Y_train, k)
    # Y_pred = np.zeros(num_test, dtype=int)  # force dtype=int in case the dataset
    #                                         # stores labels as float-point numbers
    # for i = 0 ... num_test-1
    #     Y_pred[i] = # the most common/frequent label in neighbors[i], you can
    #                 # implement it by using np.unique
    # return Y_pred

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return Y_pred

#Problem 1-step4
def compute_error_rate(ypred, ytrue):
    """
    Compute error rate given the predicted results and true lable.
    Inputs:
    - ypred: array of prediction results.
    - ytrue: array of true labels.
        ypred and ytrue should be of same length.
    Output:
    - error rate: float number indicating the error in percentage
                    (i.e., a number between 0 and 100).
    """
    # Here is the pseudo-code:
    # err = 0
    # for i = 0 ... num_test - 1
    #     err = err + (ypred[i] != ytrue[i])  # generalizes to multiple classes
    # error_rate = err / num_test * 100
    # return error_rate
    #
    # Advanced (optional): 
    #   implement it in one line by using vector operation and the `mean` function

    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return error_rate

def problem2():
    """
    copy your solutions of problem 2 to this function
    DONOT copy the code for plotting 

    Outputs:
    - error_rates: A numpy array of size (len(trials_size),) which store error rates for different example size
    - cverror_rates: A numpy array of size (len(trials_fold),) which store error rates for different fold size
    """
    import os
    import gzip

    DATA_URL = 'http://yann.lecun.com/exdb/mnist/'

    # Download and import the MNIST dataset from Yann LeCun's website.
    # Each image is an array of 784 (28x28) float values  from 0 (white) to 1 (black).
    def load_data():
        x_tr = load_images('train-images-idx3-ubyte.gz')
        y_tr = load_labels('train-labels-idx1-ubyte.gz')
        x_te = load_images('t10k-images-idx3-ubyte.gz')
        y_te = load_labels('t10k-labels-idx1-ubyte.gz')

        return x_tr, y_tr, x_te, y_te

    def load_images(filename):
        maybe_download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=16)
        return data.reshape(-1, 28 * 28) / np.float32(256)

    def load_labels(filename):
        maybe_download(filename)
        with gzip.open(filename, 'rb') as f:
            data = np.frombuffer(f.read(), np.uint8, offset=8)
        return data

    # Download the file, unless it's already here.
    def maybe_download(filename):
        if not os.path.exists(filename):
            from urllib.request import urlretrieve
            print("Downloading %s" % filename)
            urlretrieve(DATA_URL + filename, filename)

    Xtrain, ytrain, Xtest, ytest = load_data()

    train_size = 10000
    test_size = 10000

    Xtrain = Xtrain[0:train_size]
    ytrain = ytrain[0:train_size]

    Xtest = Xtest[0:test_size]
    ytest = ytest[0:test_size]

    # problem 2.1
    #  nbatches must be an even divisor of test_size. Increase if you run out of memory 
    if test_size > 1000:
        nbatches = 50
    else:
        nbatches = 5

    # Let us first set up the index of each batch. 
    # After running the next line, 'batches' will be a 2D array sized nbatches-by-m,
    # where m = test_size / nbatches.
    # batches[i] stores the indices (out of 0...test_size-1) for the i-th batch
    # You can run 'print(batches[3])' etc to witness the value of 'batches'.
    batches = np.array_split(np.arange(test_size), nbatches)
    ypred = np.zeros_like(ytest)
    trial_sizes = [100, 1000, 2500, 5000, 7500, 10000]
    trials = len(trial_sizes)
    error_rates = [0]*trials
    k = 1

    # Here is the pseudo code:
    # 
    # for t = 0 ... trials-1  # loop over different number of training examples
    # 	trial_size = trial_sizes[t]
    # 	trial_X = Xtrain[...] # extract trial_size number of training examples from the whole training set
    # 	trial_Y = Ytrain[...] # extract the corresponding labels
    # 	for i = 0…nbatches—1
    # 		ypred[...] = # call knn_predict to classify the i-th batch of test examples.
    #                  # You should use 'batches' to get the indices for batch i.
    #                  # Then store the predicted labels also in the corresponding
    #                  # elements of ypred, so that after the loop over i completes,
    #                  # ypred will hold exactly the predicted labels of all test examples.
    # 	error_rate[t] = # call compute_error_rate to compute the error rate by 
    #                     comparing ypred against ytest
    #   print a line like '#tr = 100, error rate = 50.3%'
    # plot the figure:
    # f = plt.figure()
    # plt.plot(...)
    # plt.xlabel(...)
    # plt.ylabel(...)
    # plt.show()


    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    return error_rates