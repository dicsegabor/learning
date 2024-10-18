import numpy as np

import tensorflow as tf
import tensorflow.keras.models
import tensorflow.keras.optimizers
import tensorflow.keras.layers
import tensorflow.keras.activations
import tensorflow.keras.callbacks
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay

import matplotlib.pyplot as plt

# import tester after importing tensorflow, to make sure correct tf version is imported
from annbsc23_p1_hw2_tester import Tester

############################# A3 #############################

tester = Tester("E5DBLC")
content = tester.get_dataset_content()

variable_names = content.splitlines()[0].split(";")
content = content.splitlines()[1:]

features = []
for line in content:
    for v in line.split(";"):
        try:
            num = np.float32(v)
        except ValueError as e:
            num = np.NAN

        features.append(num)

n_variables = len(variable_names)
n_examples = len(content)

features_noisy = np.array(features, dtype=np.float32).reshape(n_examples, n_variables)[
    :, :-1
]
labels = features_noisy[:, -1]

print("A3 test -", end=" ")
tester.test("dataset_load", features_noisy, labels)

############################# B2 #############################

features = np.copy(features_noisy)
noise = np.copy(features_noisy[:, 6:10])

noise[~np.isnan(noise)] = 1.0

features = np.concatenate((features, noise), axis=1)

features[np.isnan(features)] = 0.0

print("B2 test -", end=" ")
tester.test("dataset_fill_missing", features)

############################# C1 #############################

p = np.random.permutation(n_examples)
labels = labels[p]
features = features[p]

split = [int(n_examples * 0.7), int(n_examples * 0.85)]
y_train, y_val, y_test = np.split(labels, split)
x_train, x_val, x_test = np.split(features, split)

print("C1 test -", end=" ")
tester.test("dataset_split", x_train, x_val, x_test, y_train, y_val, y_test)

############################# D3 #############################

tf.keras.utils.set_random_seed(42)
reg_model = tf.keras.models.Sequential()
reg_model.add(tf.keras.layers.Dense(50, activation="tanh", input_dim=x_train.shape[1]))
reg_model.add(tf.keras.layers.Dense(30, activation="relu"))
reg_model.add(tf.keras.layers.Dense(1))

reg_model.compile(
    optimizer=tf.keras.optimizers.SGD(learning_rate=0.0001),
    loss="mse",
    metrics=[tf.keras.metrics.MeanAbsoluteError()],
)

print("D3 test -", end=" ")
tester.test("reg_model_architecture", reg_model)

############################# E #############################

earlystopping_callback = tf.keras.callbacks.EarlyStopping(
    monitor="val_loss", patience=5
)

history = reg_model.fit(
    x_train,
    y_train,
    validation_data=(x_val, y_val),
    batch_size=200,
    epochs=400,
    verbose=0,
    callbacks=[earlystopping_callback],
)

tr_mse = history.history["loss"]
val_mse = history.history["val_loss"]

plt.plot(tr_mse, label="J_train")
plt.plot(val_mse, label="J_val")
plt.ylim((0, 4))
plt.xlabel("Number of epochs")
plt.ylabel("Cost (J)")
plt.legend()
plt.show()

tr_mae = history.history["mean_absolute_error"]
val_mae = history.history["val_mean_absolute_error"]

plt.plot(tr_mae, label="J_train")
plt.plot(val_mae, label="J_val")
plt.ylim((0, 4))
plt.xlabel("Number of epochs")
plt.ylabel("Cost (J)")
plt.legend()
plt.show()

test_mse, _ = reg_model.evaluate(x_test, y_test)
y_test_predicted = reg_model.predict(x_test).flatten()
test_mae = np.mean(np.abs(y_test_predicted - y_test))

for i in range(5):
    rand_ind = np.random.randint(y_test.size)
    single_test = x_test[rand_ind]
    predicted = reg_model.predict(
        np.array(
            [
                single_test,
            ]
        ),
        verbose=0,
    )
    out = (
        str(i)
        + ". Test value: "
        + str(y_test[rand_ind])
        + " -> Predicted: "
        + str(predicted[0, 0])
    )
    print(out)

print("E test -", end=" ")
tester.test("reg_model_learning", test_mse, test_mae)

############################# F1 #############################


def divide_into_categories(values, cat_num=3):
    sort_indexes = np.argsort(values)
    ti = (np.floor(values.size / cat_num)).astype(int)

    values = values[sort_indexes]

    bins = []
    for i in range(1, cat_num):
        bins.append(values[i * ti])

    values = np.digitize(values, bins, right=False)
    return values[sort_indexes.argsort()]


cat_labels = divide_into_categories(labels)

split = [int(n_examples * 0.7), int(n_examples * 0.85)]
y_cat_train, y_cat_val, y_cat_test = np.split(cat_labels, split)

print("F1 test -", end=" ")
tester.test("cl_dataset", y_cat_train, y_cat_val, y_cat_test)

############################# G #############################


def create_one_hot(values):
    oh = np.zeros((values.size, values.max() + 1))
    oh[np.arange(values.size), values] = 1

    return oh


y_onehot_train = create_one_hot(y_cat_train)
y_onehot_val = create_one_hot(y_cat_val)
y_onehot_test = create_one_hot(y_cat_test)

print("G test -", end=" ")
tester.test("cl_onehot", y_onehot_train, y_onehot_val, y_onehot_test)

############################# H2 #############################

tf.keras.utils.set_random_seed(42)
cl_model = tf.keras.models.Sequential()
cl_model.add(tf.keras.layers.Dense(20, activation="relu", input_dim=x_train.shape[1]))
cl_model.add(tf.keras.layers.Dropout(0.2))
cl_model.add(tf.keras.layers.Dense(20, activation="relu"))
cl_model.add(tf.keras.layers.Dropout(0.2))
cl_model.add(tf.keras.layers.Dense(10, activation="relu"))
cl_model.add(tf.keras.layers.Dropout(0.2))
cl_model.add(tf.keras.layers.Dense(3, activation="softmax"))

cl_model.compile(
    optimizer=tf.keras.optimizers.SGD(learning_rate=0.0008),
    loss="categorical_crossentropy",
    metrics=["accuracy"],
)

print("H2 test -", end=" ")
tester.test("cl_model_architecture", cl_model)

############################# I #############################

earlystopping_callback = tf.keras.callbacks.EarlyStopping(
    monitor="val_loss", patience=10
)

history = cl_model.fit(
    x_train,
    y_onehot_train,
    validation_data=(x_val, y_onehot_val),
    batch_size=100,
    epochs=1500,
    verbose=0,
    callbacks=[earlystopping_callback],
)

tr_losses = history.history["loss"]
val_losses = history.history["val_loss"]

plt.clf()
plt.plot(tr_losses, label="J_train")
plt.plot(val_losses, label="J_val")
y_lim_top = np.maximum(np.amax(val_losses[2:]), np.amax(tr_losses[2:])) * 1.5
plt.ylim((0, y_lim_top))
plt.xlabel("Number of epochs")
plt.ylabel("Cost (J)")
plt.legend()
plt.show()

tr_accs = history.history["accuracy"]
val_accs = history.history["val_accuracy"]

plt.clf()
plt.plot(tr_accs, label="acc_train")
plt.plot(val_accs, label="acc_val")
plt.ylim((0.0, 1.0))
plt.xlabel("Number of epochs")
plt.ylabel("Accuracy")
plt.legend()
plt.show()

test_ce, test_acc = cl_model.evaluate(x_test, y_onehot_test, verbose=1)

y_prediction = cl_model.predict(x_test)
y_prediction = np.argmax(y_prediction, axis=1)
y_test = np.argmax(y_onehot_test, axis=1)
cm = confusion_matrix(y_test, y_prediction, normalize="pred")

disp = ConfusionMatrixDisplay(confusion_matrix=cm)
disp.plot()
plt.show()

print("I test -", end=" ")
tester.test("cl_model_learning", test_ce, test_acc)
tester.print_all_tests_successful()
