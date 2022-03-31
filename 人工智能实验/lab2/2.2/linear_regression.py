from sklearn.preprocessing import PolynomialFeatures
import numpy as np
from sklearn import linear_model
import matplotlib.pyplot as plt

m=100
X = 6*np.random.rand(m,1) - 3
Y = 0.5*X**2 + X + 2 + np.random.randn(m,1)
lr=linear_model.LinearRegression()

poly_feacures = PolynomialFeatures(degree=2,include_bias=False)
X_poly = poly_feacures.fit_transform(X)

lr.fit(X_poly,Y)

X = np.sort(X,axis=0)
Y = 0.5*X**2 + X + 2 + np.random.randn(m,1)
print(X)

plt.scatter(X,Y)
plt.plot(X,lr.predict(poly_feacures.fit_transform(X)),color='red',linewidth=3)
plt.show()
