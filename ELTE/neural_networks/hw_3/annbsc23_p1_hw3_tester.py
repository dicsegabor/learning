
#
# Automatic tests for ANN BSc part1, 2023 spring, HW3
#
# Authors: Viktor Varga
#

import os
import urllib
import numpy as np

import tensorflow as tf
import tensorflow.keras.models
import tensorflow.keras.optimizers
import tensorflow.keras.layers
import tensorflow.keras.callbacks
import tensorflow.keras.activations

N_TASKS = 3

TASK_LIST = ["DK7UAQ, B/3, E/2, H/3", "AAZBJW, B/1, E/2, H/3", "AFCV8A, B/3, E/1, H/1", "AMU435, B/3, E/1, H/1", \
             "AYLV4Z, B/1, E/2, H/3", "A73EXW, B/2, E/2, H/3", "A9CQZ0, B/1, E/2, H/1", "BEGEAJ, B/1, E/1, H/1", \
             "BKBDWF, B/3, E/1, H/3", "BLKV0U, B/2, E/1, H/2", "BMCPB3, B/1, E/1, H/3", "BNBQ2Z, B/3, E/2, H/3", \
             "BORB7G, B/1, E/2, H/1", "BT9R0A, B/1, E/1, H/1", "BU6T68, B/3, E/1, H/1", "BXUMGO, B/2, E/1, H/2", \
             "CBJ6AX, B/2, E/1, H/1", "CGLTTT, B/3, E/2, H/2", "CI6U9I, B/3, E/2, H/1", "CLIV4Q, B/2, E/2, H/1", \
             "CYCSS7, B/3, E/1, H/3", "C6A1S7, B/2, E/2, H/3", "C6UCIF, B/1, E/1, H/2", "C9M2NM, B/2, E/2, H/1", \
             "DAKXMB, B/2, E/2, H/2", "DAX8UM, B/3, E/1, H/1", "DBNW9B, B/3, E/1, H/2", "DCPFEX, B/2, E/2, H/1", \
             "DFI46C, B/3, E/2, H/3", "DIZWYJ, B/2, E/1, H/3", "DLQBAW, B/3, E/1, H/2", "DLY99J, B/2, E/1, H/3", \
             "DOV7LK, B/3, E/1, H/2", "DP824O, B/3, E/2, H/3", "DUOINC, B/2, E/2, H/1", "DVBZPO, B/3, E/1, H/2", \
             "DWB17O, B/3, E/2, H/1", "DZUYAY, B/1, E/2, H/3", "D73SON, B/2, E/1, H/1", "EBMG1Y, B/2, E/1, H/2", \
             "ECNQ22, B/3, E/2, H/2", "EHNKND, B/3, E/2, H/1", "EHWZPB, B/1, E/2, H/2", "EPL5TY, B/3, E/1, H/3", \
             "EQFF2Z, B/3, E/1, H/2", "EV6TBF, B/1, E/2, H/2", "EXFTXQ, B/2, E/2, H/2", "EXYXWD, B/3, E/1, H/1", \
             "E5CXIJ, B/2, E/2, H/1", "E5DBLC, B/1, E/2, H/2", "E59WA4, B/1, E/1, H/2", "FBGWXP, B/2, E/2, H/3", \
             "FB7VPB, B/1, E/2, H/2", "FH8BYN, B/3, E/2, H/1", "FLZ5UY, B/1, E/2, H/2", "FN9NBP, B/1, E/2, H/3", \
             "FPNH64, B/1, E/1, H/1", "FTVFEN, B/2, E/1, H/2", "FY3GF5, B/1, E/2, H/1", "F4NNK4, B/1, E/1, H/2", \
             "F65B8O, B/2, E/2, H/1", "GAKRVW, B/2, E/1, H/2", "GHEK6K, B/2, E/2, H/2", "GH8D1Y, B/2, E/1, H/1", \
             "GJJ3JG, B/1, E/2, H/2", "GKVZ6P, B/2, E/2, H/3", "HBS6L5, B/1, E/2, H/1", "HB5UGA, B/3, E/1, H/1", \
             "HCYGTM, B/3, E/1, H/1", "HFNKIH, B/3, E/1, H/3", "HHMCPC, B/1, E/1, H/1", "HHSLRA, B/3, E/1, H/2", \
             "HM37UQ, B/2, E/1, H/2", "HQLQ7G, B/1, E/1, H/3", "HSMAUW, B/1, E/1, H/3", "H0IZYC, B/1, E/1, H/1", \
             "H15R0C, B/2, E/1, H/3", "H2MJ2U, B/1, E/2, H/1", "H9REJA, B/2, E/1, H/2", "IC5JV5, B/1, E/1, H/3", \
             "INXGWX, B/3, E/2, H/3", "IPTY48, B/3, E/2, H/3", "ITFPBP, B/2, E/2, H/2", "I5LPC6, B/2, E/1, H/1", \
             "I5WFV1, B/3, E/1, H/1", "JE0RHR, B/3, E/2, H/3", "JFD2SO, B/1, E/2, H/3", "JL8WEQ, B/3, E/1, H/1", \
             "JMDPHK, B/1, E/1, H/2", "JM9MSF, B/2, E/1, H/1", "JNEC51, B/2, E/2, H/1", "JW3PJY, B/1, E/2, H/3", \
             "J04HYX, B/1, E/1, H/2", "J2868O, B/1, E/1, H/2", "J5XTQJ, B/1, E/1, H/2", "KEBEI8, B/3, E/1, H/1", \
             "KJC7IU, B/3, E/1, H/3", "KL43GM, B/1, E/2, H/2", "KOOS7E, B/2, E/1, H/1", "KQQTNM, B/3, E/2, H/1", \
             "KQ3IZS, B/2, E/1, H/3", "KR0SOX, B/3, E/2, H/1", "KVCWRM, B/3, E/2, H/1", "K3JAXN, B/3, E/2, H/1", \
             "LCMZKU, B/1, E/2, H/2", "LCRXUR, B/2, E/2, H/2", "LKG7D7, B/3, E/1, H/1", "LPLLK8, B/2, E/2, H/1", \
             "L030TC, B/1, E/1, H/2", "L74BNY, B/2, E/1, H/1", "MBNYAU, B/2, E/1, H/3", "MDS0R8, B/2, E/1, H/3", \
             "MM2IZZ, B/3, E/1, H/1", "MNZVUM, B/2, E/1, H/1", "MZU7UO, B/3, E/1, H/3", "M2RVEM, B/3, E/2, H/3", \
             "M4960M, B/3, E/2, H/1", "NMA361, B/2, E/2, H/1", "NN5NT0, B/1, E/1, H/2", "NRXJFK, B/2, E/1, H/3", \
             "NTBGJ1, B/1, E/1, H/2", "NUG9NG, B/1, E/2, H/3", "NXLMTE, B/2, E/1, H/3", "OGOQJL, B/3, E/2, H/1", \
             "ONM7YZ, B/2, E/2, H/3", "OO4KIT, B/1, E/2, H/3", "OQQ4Q8, B/2, E/1, H/1", "ORA5FM, B/2, E/1, H/1", \
             "OR0S2G, B/2, E/2, H/3", "O053EX, B/3, E/1, H/1", "O8901S, B/2, E/2, H/3", "PB3PJH, B/2, E/2, H/3", \
             "PCD3OW, B/3, E/1, H/1", "PEXZ1E, B/2, E/2, H/3", "PF2YKK, B/2, E/2, H/3", "PLQFPN, B/3, E/1, H/1", \
             "PQWR5B, B/3, E/1, H/1", "PST8RA, B/3, E/2, H/2", "PZ20TK, B/1, E/2, H/1", "P2LJYA, B/1, E/1, H/2", \
             "P950GT, B/3, E/1, H/2", "QEQRMY, B/3, E/2, H/1", "QGSI2B, B/1, E/2, H/2", "QI198X, B/2, E/2, H/1", \
             "QJ6007, B/2, E/2, H/3", "Q1D5GO, B/3, E/2, H/2", "Q14H22, B/1, E/2, H/3", "RASWIQ, B/1, E/1, H/3", \
             "RDE3CS, B/3, E/1, H/2", "RHVBKN, B/1, E/2, H/2", "RMXRFG, B/3, E/2, H/2", "RNBJ4X, B/2, E/1, H/2", \
             "R532OV, B/1, E/1, H/1", "SA0MPZ, B/3, E/1, H/2", "SN20U1, B/2, E/2, H/2", "S6HQD2, B/1, E/2, H/3", \
             "TB9FOP, B/3, E/1, H/3", "T3PUZR, B/2, E/2, H/3", "T6WVH6, B/2, E/1, H/2", "T9NQAI, B/1, E/2, H/1", \
             "U0815G, B/3, E/2, H/3", "VDN8WH, B/2, E/2, H/3", "VWD1ZR, B/1, E/1, H/2", "V4ASUI, B/2, E/2, H/1", \
             "WKC5V4, B/1, E/2, H/1", "WLIR82, B/1, E/1, H/2", "WW5YY3, B/3, E/2, H/2", "W1IGER, B/1, E/2, H/1", \
             "XG8ZJ9, B/2, E/1, H/1", "XK2G4R, B/2, E/1, H/2", "XN661O, B/3, E/2, H/3", "XP2D8L, B/1, E/1, H/3", \
             "XQ3QM8, B/1, E/1, H/3", "XWAGNC, B/1, E/1, H/3", "X2ZA3U, B/3, E/2, H/3", "X3F10S, B/3, E/2, H/2", \
             "YCY3LB, B/2, E/1, H/3", "YDI2TP, B/1, E/2, H/1", "YJA6RK, B/2, E/2, H/2", "YLCD29, B/1, E/2, H/3", \
             "YO0D0V, B/2, E/1, H/3", "Y8TD56, B/3, E/1, H/1", "ZBDLRL, B/2, E/2, H/3", "ZELLN3, B/1, E/1, H/1", \
             "ZFQWVT, B/2, E/1, H/1", "ZJSZQ2, B/1, E/1, H/1", "Z3QVU3, B/3, E/1, H/1", "Z4PRN0, B/3, E/2, H/2", \
             "Z4WB8E, B/2, E/2, H/2"]

TASK_DATA = {
             'B_shapes': {1: 955, 2: 704, 3: 570},
             'B_n_cats': {1: 5, 2: 4, 3: 3},
             'E_valid_black_pix_ratio': {1: (0., 0.04), 2: (0.05, 0.3)},
             'H_datagen_params': {1: {'cal_f':True, 'l_shift_r':0.2},
                                  2: {'ear_r':0.2, 'l_shift_r':0.1},
                                  3: {'cal_f':True, 'ear_r':0.1}}
             }

class Tester:

    '''
    Member fields:

        TESTS_DICT: dict{test_name - str: test function - Callable}

        neptun_code: str; letter characters converted to capital
        student_tasks: dict{task_name - str: task_id - int}

        # STORED DATA FROM PREVIOUS TESTS

        relevant_idxs: ndarray(n_relevant_idxs) of int
        xs: ndarray(n_samples, 160, 160, 3) of uint8
        ys: ndarray(n_samples,) of int

        # RESULT OF LASTEST PREVIOUS TEST RUNS
        test_results: dict{test_name - str: success - bool}

    '''

    def __init__(self, neptun_code, debug_mode=False):
        '''
        Load assigned tasks for each student (by neptun_code) or specify exact task IDs while passing debug_mode=True.
        Paramters:
            neptun_code: str 
                         OR dict(n_tasks){str: int} of int; if 'debug_mode' is True; the exact tasks given
            debug_mode: bool
        '''
        self.relevant_idxs = None
        self.xs = None
        self.ys = None

        self.TESTS_DICT = {'B': self.__test_B,
                           'C': self.__test_C,
                           'E': self.__test_E,
                           'F': self.__test_F,
                           'G': self.__test_G,
                           'H': self.__test_H,
                           'J': self.__test_J}

        self.test_results = {k: False for k in self.TESTS_DICT.keys()}

        if debug_mode:
            assert type(neptun_code) == dict
            assert len(neptun_code) == N_TASKS
            self.student_tasks = neptun_code
        else:
            self.neptun_code = neptun_code.strip().upper()
            self.__get_student_tasks()

    def test(self, test_name, *args):
        '''
        Parameters:
            test_name: str
            *args: varargs; the arguments for the selected test
        '''
        if test_name not in self.TESTS_DICT:
            assert False, "Tester error: Invalid test name: " + str(test_name)

        self.test_results[test_name] = False
        test_func = self.TESTS_DICT[test_name]
        test_func(*args)
        self.test_results[test_name] = True    # only executed if no assert happened during test

    def print_all_tests_successful(self):
        if all(list(self.test_results.values())):
            print("Tester: All tests were successful.")

    # PRIVATE

    def __get_student_tasks(self):
        '''
        Sets self.student_tasks.
        '''
        for entry in TASK_LIST:
            words = [word.strip() for word in entry.split(',')]
            assert len(words) == N_TASKS+1, "Tester error: Invalid task entry length: " + str(words)
            neptun_code = words[0]
            assert len(neptun_code) == 6, "Tester error: Invalid neptun code format: " + str(neptun_code)
            if neptun_code.upper() != self.neptun_code:
                continue
            # neptun code found
            assert all([len(word) == 3 for word in words[1:]]), "Tester error: Invalid task format: " + str(words)
            self.student_tasks = {word[0]: int(word[-1]) for word in words[1:]}
            return
        # neptun code not found
        assert False, "Tester: Neptun code was not found in the student list: " + str(self.neptun_code)


    # TESTS

    def __test_B(self, *args):
        assert len(args) == 1, "Tester error: __test_B() expects 1 parameter: relevant_idxs. "
        relevant_idxs, = args

        assert type(relevant_idxs) == np.ndarray, "Tester: relevant_idxs should be a numpy array."
        assert relevant_idxs.shape == (TASK_DATA['B_shapes'][self.student_tasks['B']],),\
                                            "Tester: relevant_idxs array shape is incorrect."
        assert relevant_idxs.dtype.kind in ['i', 'u'],\
                    "Tester: relevant_idxs stores indices, therefore it should have a signed or unisgned integer dtype."
        
        # unique idxs
        assert np.unique(relevant_idxs).shape[0] == relevant_idxs.shape[0], "Tester: all indices in relevant_idxs must be unique."

        self.relevant_idxs = relevant_idxs
        print("Tester: Relevant image indices OK")


    def __test_C(self, *args):
        assert len(args) == 1, "Tester error: __test_C() expects 1 parameter: bboxes. "
        bboxes, = args

        assert self.relevant_idxs is not None, "Tester error: Run test B before running test C."

        assert type(bboxes) == np.ndarray, "Tester: bboxes should be a numpy array."
        assert bboxes.ndim == 2, "Tester: bboxes should be a 2D array."
        assert 4000 < bboxes.shape[0] < 10000, "Tester: bboxes array dim#0 length should be between 4000 and 10000."
        assert bboxes.shape[1] == 6, "Tester: bboxes array dim#1 length should be 6."
        assert bboxes.dtype.kind in ['i', 'u'], "Tester: bboxes should have a signed or unisgned integer dtype."
        
        # assert bboxes[:,4] stores new category indices
        n_cats = TASK_DATA['B_n_cats'][self.student_tasks['B']]
        assert np.array_equal(np.unique(bboxes[:,4]), np.arange(n_cats)), \
                    "Tester: bboxes array contains invalid values in column#4; category indices should be from [0, n_categories-1]"

        # assert bbox area is not negative
        assert np.all(bboxes[:,0] <= bboxes[:,2]) and np.all(bboxes[:,1] <= bboxes[:,3]), \
                    "Tester: bboxes array contains invalid values in column#0..3; left/top boundaries should have a smaller coordinate than right/bottom boundaries."

        # assert bbox boundaries are within original image resolution (320x240)
        assert np.all(bboxes[:,0:4:2] >= 0) and np.all(bboxes[:,0:4:2] < [240,320]), \
                    "Tester: bboxes array contains invalid values in column#0..3; boundaries should be pointing to valid coordinates of a 320x240 (xy) image."

        # assert all image indices are among indices from the relevant_idxs array
        assert np.all(np.isin(bboxes[:,5], self.relevant_idxs)), \
                    "Tester: bboxes array contains invalid values in column#5; some image indices in column#5 are not among indices from the relevant_idxs array."

        print("Tester: Bounding boxes OK")

    def __test_E(self, *args):
        assert len(args) == 2, "Tester error: __test_E() expects 2 parameterd: xs, ys. "
        xs, ys = args

        assert type(xs) == np.ndarray, "Tester: xs should be a numpy array."
        assert type(ys) == np.ndarray, "Tester: ys should be a numpy array."
        assert xs.ndim == 4, "Tester: xs should be a 4D array."
        assert ys.ndim == 1, "Tester: ys should be a 1D array."
        assert xs.shape[0] == ys.shape[0], "Tester: xs and ys dim#0 length must match."
        assert xs.shape[0] > 600, "Tester: too few items in xs, ys (dim#0)."
        assert xs.shape[1:] == (160,160,3), "Tester: incorrect xs shape; xs must contain color images with a resolution of 160x160."
        assert xs.dtype == np.uint8, "Tester: xs should have an uint8 dtype, similar to the original images."
        assert ys.dtype.kind in ['i', 'u'], "Tester: ys should have a signed or unisgned integer dtype."

        # assert all categories are present in ys with a sufficient frequency
        u_ys, c_ys = np.unique(ys, return_counts=True)
        n_cats = TASK_DATA['B_n_cats'][self.student_tasks['B']]
        assert np.array_equal(u_ys, np.arange(n_cats)), \
                    "Tester: category indices in ys should be exactly from [0, n_categories-1]"
        assert np.all(c_ys / np.sum(c_ys) > 0.1), \
                    "Tester: too few items in one of the categories in ys."

        # check ratio of black pixels (significantly different if padding is used)
        valid_black_ratio_min, valid_black_ratio_max = TASK_DATA['E_valid_black_pix_ratio'][self.student_tasks['E']]
        assert valid_black_ratio_min < np.count_nonzero(xs == 0) / xs.size < valid_black_ratio_max, \
                    "Tester: invalid black pixel ratio in xs; cropping of xs samples might be incorrect."

        self.xs = xs
        self.ys = ys
        print("Tester: Image cropping & category labels OK")

    def __test_F(self, *args):
        assert len(args) == 6, "Tester error: __test_F() expects 6 parameters:" +\
                                                        "xs_train, xs_val, xs_test, ys_train, ys_val, ys_test. "
        xs_train, xs_val, xs_test, ys_train, ys_val, ys_test = args

        assert (self.xs is not None) and (self.ys is not None), "Tester error: Run test E before running test F."

        assert type(xs_train) == np.ndarray, "Tester: xs_train should be a numpy array."
        assert type(xs_val) == np.ndarray, "Tester: xs_val should be a numpy array."
        assert type(xs_test) == np.ndarray, "Tester: xs_test should be a numpy array."
        assert type(ys_train) == np.ndarray, "Tester: ys_train should be a numpy array."
        assert type(ys_val) == np.ndarray, "Tester: ys_val should be a numpy array."
        assert type(ys_test) == np.ndarray, "Tester: ys_test should be a numpy array."

        # assert split sizes correct
        assert xs_train.shape[0] == ys_train.shape[0], "Tester: xs splits should match in dim#0 length with ys splits."
        assert xs_val.shape[0] == ys_val.shape[0], "Tester: xs splits should match in dim#0 length with ys splits."
        assert xs_test.shape[0] == ys_test.shape[0], "Tester: xs splits should match in dim#0 length with ys splits."
        assert abs(xs_train.shape[0] - xs_val.shape[0]*3) < 4, "Tester: xs_train or xs_val split sizes are incorrect."
        assert abs(xs_train.shape[0] - xs_test.shape[0]*3) < 4, "Tester: xs_train or xs_test split sizes are incorrect."

        # assert  combined shape unchanged
        concat_xs = np.concatenate([xs_train, xs_val, xs_test], axis=0)
        concat_ys = np.concatenate([ys_train, ys_val, ys_test], axis=0)
        assert concat_xs.shape == self.xs.shape, "Tester: concatenated xs splits do not match original xs array shape."
        assert concat_ys.shape == self.ys.shape, "Tester: concatenated ys splits do not match original ys array shape."
        
        # assert shuffled
        assert not np.array_equal(self.ys, concat_ys), "Tester: xs/ys arrays were not shuffled before splitting."

        print("Tester: Dataset split OK")

    def __test_G(self, *args):
        assert len(args) == 1, "Tester error: __test_G() expects 1 parameter: model_ft. "
        model_ft, = args
        assert 'categorical_crossentropy' in str(model_ft.loss).lower(), "Tester: Incorrect classification loss."
        assert 'sparse_categorical_crossentropy' in str(model_ft.loss).lower(), "Tester: Use the sparse loss instead, see task details."
        assert 'softmax' in str(model_ft.layers[-1].activation).lower(), "Tester: Incorrect activation function in last layer."
        
        n_cats = TASK_DATA['B_n_cats'][self.student_tasks['B']]
        assert model_ft.layers[-1].output.shape[-1] == n_cats, "Tester: Incorrect shape of network output; Check the number of categories."
        
        print("Tester: Model architecture OK")

    def __test_H(self, *args):
        assert len(args) == 3, "Tester error: __test_H() expects 3 parameters: "+\
                                        "datagen, train_generator, val_generator. "
        datagen, train_generator, val_generator = args

        # assert correct ImageDataGenerator paramters
        shared_params = {'ion_ran':30, 'h_shift_r':0.25, 't_shift_r':0.25, 'ntal_f':True, 'll_mo':'wrap', 'oo':[0.8, 1.2]}
        ext_params = TASK_DATA['H_datagen_params'][self.student_tasks['H']]

        for k, v in datagen.__dict__.items():
            for k_part in shared_params.keys():
                if k_part in k:
                    assert v == shared_params[k_part], "Tester: data generator parameter '" + str(k) + "' does not match required value."
            for k_part in ext_params.keys():
                if k_part in k:
                    assert v == ext_params[k_part], "Tester: data generator parameter '" + str(k) + "' does not match required value."

        # assert correct generated batch types, shapes
        batch_tup_train = next(train_generator)
        batch_tup_val = next(val_generator)
        assert len(batch_tup_train) == 2, "Tester: train_generator should yield tuples of length 2, (xs, ys)."
        assert len(batch_tup_val) == 2, "Tester: val_generator should yield tuples of length 2, (xs, ys)."

        batch_xs_train, batch_ys_train = batch_tup_train
        batch_xs_val, batch_ys_val = batch_tup_val

        assert type(batch_xs_train) == np.ndarray, "Tester: train_generator should yield a tuple of two numpy arrays."
        assert type(batch_ys_train) == np.ndarray, "Tester: train_generator should yield a tuple of two numpy arrays."
        assert type(batch_xs_val) == np.ndarray, "Tester: val_generator should yield a tuple of two numpy arrays."
        assert type(batch_ys_val) == np.ndarray, "Tester: val_generator should yield a tuple of two numpy arrays."

        assert batch_xs_train.shape[:1] == batch_ys_train.shape,\
                             "Tester: shape mismatch between train_generator input-output batches."
        assert batch_xs_val.shape[:1] == batch_ys_val.shape,\
                             "Tester: shape mismatch between val_generator input-output batches."
        assert batch_xs_train.shape[1:] == batch_xs_val.shape[1:] == (160, 160, 3),\
                    "incorrect shape for train/val_generator input batches; should be (batch_size, 160, 160, 3)"

        # check dtype of generated samples
        assert batch_xs_train.dtype == np.float32, "Tester: train_generator input image samples must be of float32 dtype."
        assert batch_xs_val.dtype == np.float32, "Tester: val_generator input image samples must be of float32 dtype."

        assert batch_ys_train.dtype.kind in ['i', 'u'], "Tester: train_generator labels should have a signed or unisgned integer dtype."
        assert batch_ys_val.dtype.kind in ['i', 'u'], "Tester: val_generator labels should have a signed or unisgned integer dtype."
        
        # check generated input sample value range
        assert -1.01 < np.amin(batch_xs_train) < 1.01, "Tester: train_generator input image samples must be scaled to [-1,1] range."
        assert -1.01 < np.amin(batch_xs_val) < 1.01, "Tester: val_generator input image samples must be scaled to [-1,1] range."

        print("Tester: Training/validation data generators OK")

    def __test_J(self, *args):
        assert len(args) == 1, "Tester error: __test_J() expects 1 parameter: test_acc. "
        test_acc, = args

        assert test_acc > 0.8, "A well trained classifier should produce an accuracy greather than 0.8."

        print("Tester: Classifier training OK")

