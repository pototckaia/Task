from keras.models import Sequential
from keras.layers import Dense
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_absolute_error 

def inputfunct(x):
    return 0.25*(np.sin(2*np.pi*x*x)+2.0)

sizeSample = 2048
start, end, step = 0, 1, 0.01
Xreal = np.arange(start, end, step)
Yreal = inputfunct(Xreal)

np.random.seed(5)
# Gaussian random noise 
X = np.random.sample([sizeSample]) % (end - start + 1) + start
Y = inputfunct(X) + 0.2*np.random.normal(0, 0.2, len(X))


model = Sequential()
model.add(Dense(8, input_dim=1, activation='relu'))
model.add(Dense(64, activation='relu'))
model.add(Dense(64, activation='relu'))
model.add(Dense(1, activation='linear'))

model.compile(optimizer='adam', loss='mse', metrics=['mse'])

# Then, the weights and biases of the neural network are adjusted in each 
# learning iteration called epoch. Not all data is processed at the same 
# time, only a certain number of batches.
nepoch = 128
nbatch = 16
model.fit(X, Y, epochs=nepoch, batch_size=nbatch)
Ylearn = model.predict(Xreal)

plt.plot(X,Y,'.', label='Raw noisy input data')
plt.plot(Xreal,Yreal, label='Actual function, not noisy', linewidth=4.0, c='black')
plt.plot(Xreal, Ylearn, label='Output of the Neural Net', linewidth=4.0, c='red')
plt.legend()
plt.savefig('lab1.png')