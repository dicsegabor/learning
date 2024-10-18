
#
# Automatic tests for Homework#2 in ELTE IK, ANN BSc course part1, 2023 spring
#
# Authors: Balint Kovacs, Viktor Varga
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

N_TASKS = 6
TASK_LIST = ["AAZBJW, A/1., B/1., C/1., D/3., F/2., H/1.", "AFCV8A, A/1., B/2., C/3., D/1., F/1., H/3.", "AMU435, A/2., B/2., C/1., D/2., F/2., H/3.", 
            "AYLV4Z, A/3., B/1., C/1., D/2., F/1., H/3.", "A73EXW, A/3., B/1., C/2., D/1., F/2., H/1.", "A9CQZ0, A/2., B/1., C/2., D/1., F/1., H/1.", 
            "BEGEAJ, A/3., B/1., C/3., D/3., F/2., H/1.", "BKBDWF, A/2., B/2., C/3., D/2., F/1., H/2.", "BLKV0U, A/3., B/1., C/2., D/3., F/1., H/2.", 
            "BMCPB3, A/1., B/1., C/3., D/3., F/2., H/3.", "BNBQ2Z, A/1., B/1., C/2., D/3., F/2., H/1.", "BORB7G, A/1., B/2., C/2., D/3., F/2., H/3.", 
            "BT9R0A, A/1., B/1., C/2., D/2., F/2., H/1.", "BU6T68, A/2., B/1., C/2., D/3., F/1., H/3.", "BXUMGO, A/1., B/1., C/3., D/2., F/2., H/3.", 
            "CBJ6AX, A/3., B/1., C/2., D/3., F/2., H/1.", "CGLTTT, A/1., B/2., C/2., D/3., F/2., H/1.", "CI6U9I, A/2., B/2., C/2., D/1., F/2., H/2.", 
            "CLIV4Q, A/2., B/2., C/2., D/3., F/1., H/3.", "CYCSS7, A/2., B/2., C/2., D/2., F/1., H/2.", "C6A1S7, A/1., B/2., C/3., D/3., F/2., H/3.", 
            "C6UCIF, A/3., B/1., C/2., D/2., F/1., H/1.", "C9M2NM, A/2., B/2., C/2., D/3., F/1., H/3.", "DAKXMB, A/2., B/2., C/1., D/2., F/2., H/1.", 
            "DAX8UM, A/1., B/2., C/2., D/1., F/2., H/1.", "DBNW9B, A/1., B/1., C/3., D/3., F/2., H/2.", "DCPFEX, A/2., B/1., C/1., D/2., F/2., H/1.", 
            "DFI46C, A/2., B/1., C/3., D/1., F/1., H/1.", "DIZWYJ, A/3., B/2., C/1., D/2., F/1., H/1.", "DLQBAW, A/1., B/2., C/1., D/1., F/2., H/2.", 
            "DLY99J, A/3., B/2., C/1., D/1., F/1., H/2.", "DOV7LK, A/1., B/2., C/2., D/2., F/2., H/2.", "DP824O, A/2., B/2., C/3., D/1., F/2., H/2.", 
            "DUOINC, A/3., B/2., C/1., D/2., F/1., H/3.", "DVBZPO, A/3., B/1., C/2., D/2., F/1., H/3.", "DWB17O, A/1., B/1., C/3., D/1., F/1., H/2.", 
            "DZUYAY, A/1., B/1., C/1., D/2., F/1., H/1.", "D73SON, A/3., B/1., C/1., D/3., F/2., H/2.", "EBMG1Y, A/3., B/1., C/3., D/2., F/1., H/3.", 
            "ECNQ22, A/3., B/1., C/1., D/2., F/1., H/2.", "EHNKND, A/2., B/1., C/2., D/3., F/2., H/1.", "EHWZPB, A/1., B/1., C/1., D/2., F/1., H/2.", 
            "EPL5TY, A/1., B/1., C/2., D/2., F/1., H/1.", "EQFF2Z, A/2., B/2., C/2., D/1., F/2., H/2.", "EV6TBF, A/3., B/2., C/2., D/3., F/2., H/3.", 
            "EXFTXQ, A/2., B/2., C/3., D/2., F/1., H/2.", "EXYXWD, A/2., B/2., C/1., D/2., F/2., H/1.", "E5CXIJ, A/1., B/2., C/3., D/1., F/1., H/2.", 
            "E5DBLC, A/3., B/2., C/1., D/3., F/1., H/2.", "E59WA4, A/3., B/2., C/3., D/3., F/1., H/1.", "FBGWXP, A/1., B/2., C/2., D/3., F/2., H/3.", 
            "FB7VPB, A/1., B/2., C/2., D/3., F/2., H/2.", "FH8BYN, A/2., B/1., C/2., D/1., F/2., H/1.", "FLZ5UY, A/1., B/2., C/1., D/3., F/2., H/3.", 
            "FN9NBP, A/3., B/2., C/3., D/2., F/2., H/3.", "FPNH64, A/2., B/1., C/1., D/2., F/2., H/1.", "FTVFEN, A/1., B/2., C/3., D/1., F/2., H/1.", 
            "FY3GF5, A/2., B/2., C/1., D/2., F/2., H/2.", "F4NNK4, A/2., B/1., C/3., D/2., F/1., H/2.", "F65B8O, A/3., B/2., C/3., D/3., F/2., H/2.", 
            "GAKRVW, A/2., B/1., C/2., D/2., F/1., H/3.", "GHEK6K, A/2., B/2., C/1., D/3., F/2., H/3.", "GH8D1Y, A/1., B/1., C/1., D/1., F/1., H/3.", 
            "GJJ3JG, A/1., B/2., C/3., D/2., F/2., H/1.", "GKVZ6P, A/1., B/2., C/3., D/3., F/2., H/3.", "HBS6L5, A/2., B/2., C/2., D/2., F/1., H/3.", 
            "HB5UGA, A/3., B/1., C/3., D/3., F/1., H/3.", "HCYGTM, A/2., B/1., C/1., D/1., F/1., H/1.", "HFNKIH, A/1., B/2., C/3., D/1., F/1., H/3.", 
            "HHMCPC, A/2., B/2., C/2., D/2., F/2., H/2.", "HHSLRA, A/1., B/1., C/1., D/1., F/1., H/2.", "HM37UQ, A/1., B/1., C/1., D/3., F/1., H/1.", 
            "HQLQ7G, A/3., B/1., C/3., D/2., F/2., H/3.", "HSMAUW, A/2., B/2., C/1., D/3., F/1., H/3.", "H0IZYC, A/2., B/2., C/1., D/3., F/2., H/1.", 
            "H15R0C, A/1., B/1., C/1., D/1., F/1., H/3.", "H2MJ2U, A/2., B/1., C/3., D/1., F/2., H/3.", "H9REJA, A/3., B/1., C/1., D/1., F/2., H/1.", 
            "IC5JV5, A/1., B/2., C/2., D/2., F/2., H/3.", "INXGWX, A/2., B/2., C/1., D/1., F/2., H/3.", "IPTY48, A/1., B/1., C/3., D/3., F/2., H/3.", 
            "ITFPBP, A/3., B/2., C/3., D/3., F/2., H/3.", "I5LPC6, A/1., B/2., C/1., D/3., F/1., H/2.", "I5WFV1, A/2., B/1., C/2., D/1., F/1., H/3.", 
            "JE0RHR, A/1., B/2., C/3., D/2., F/1., H/3.", "JFD2SO, A/1., B/1., C/2., D/2., F/2., H/2.", "JL8WEQ, A/2., B/2., C/1., D/2., F/1., H/1.", 
            "JMDPHK, A/2., B/1., C/3., D/1., F/1., H/1.", "JM9MSF, A/2., B/1., C/1., D/3., F/2., H/2.", "JNEC51, A/1., B/2., C/2., D/3., F/1., H/2.", 
            "JW3PJY, A/3., B/2., C/1., D/2., F/1., H/3.", "J04HYX, A/3., B/1., C/2., D/2., F/2., H/1.", "J2868O, A/1., B/1., C/2., D/3., F/1., H/2.", 
            "J5XTQJ, A/2., B/1., C/3., D/3., F/1., H/3.", "KEBEI8, A/2., B/1., C/3., D/3., F/1., H/1.", "KJC7IU, A/1., B/1., C/3., D/2., F/2., H/1.", 
            "KL43GM, A/3., B/1., C/3., D/3., F/2., H/3.", "KOOS7E, A/2., B/1., C/3., D/3., F/2., H/1.", "KQQTNM, A/1., B/2., C/3., D/3., F/1., H/1.", 
            "KQ3IZS, A/3., B/2., C/2., D/3., F/1., H/3.", "KR0SOX, A/2., B/2., C/3., D/1., F/1., H/2.", "KVCWRM, A/1., B/1., C/3., D/2., F/1., H/1.", 
            "K3JAXN, A/1., B/2., C/2., D/2., F/1., H/2.", "LCMZKU, A/2., B/2., C/2., D/3., F/1., H/2.", "LCRXUR, A/3., B/2., C/1., D/2., F/1., H/2.", 
            "LKG7D7, A/2., B/1., C/3., D/2., F/1., H/1.", "LPLLK8, A/2., B/1., C/2., D/3., F/1., H/2.", "L030TC, A/2., B/1., C/3., D/1., F/1., H/3.", 
            "L74BNY, A/1., B/2., C/1., D/1., F/2., H/1.", "MBNYAU, A/3., B/1., C/2., D/3., F/2., H/1.", "MDS0R8, A/1., B/1., C/3., D/3., F/2., H/1.", 
            "MM2IZZ, A/3., B/1., C/2., D/2., F/2., H/2.", "MNZVUM, A/1., B/2., C/2., D/3., F/1., H/1.", "MZU7UO, A/2., B/1., C/3., D/2., F/2., H/1.", 
            "M2RVEM, A/3., B/2., C/1., D/2., F/1., H/2.", "M4960M, A/1., B/2., C/2., D/3., F/2., H/3.", "NMA361, A/3., B/2., C/2., D/3., F/1., H/1.", 
            "NN5NT0, A/2., B/2., C/3., D/3., F/2., H/3.", "NRXJFK, A/3., B/1., C/3., D/2., F/1., H/3.", "NTBGJ1, A/1., B/1., C/2., D/1., F/1., H/1.", 
            "NUG9NG, A/2., B/2., C/2., D/2., F/2., H/2.", "NXLMTE, A/2., B/1., C/3., D/1., F/1., H/2.", "OGOQJL, A/3., B/1., C/3., D/1., F/1., H/1.", 
            "ONM7YZ, A/1., B/2., C/2., D/1., F/1., H/1.", "OO4KIT, A/3., B/2., C/2., D/2., F/2., H/2.", "OQQ4Q8, A/3., B/2., C/2., D/1., F/2., H/2.", 
            "ORA5FM, A/1., B/2., C/2., D/2., F/1., H/2.", "OR0S2G, A/2., B/2., C/1., D/2., F/1., H/2.", "O053EX, A/3., B/2., C/3., D/2., F/1., H/3.", 
            "O8901S, A/3., B/1., C/3., D/3., F/1., H/2.", "PB3PJH, A/3., B/2., C/3., D/2., F/1., H/3.", "PCD3OW, A/1., B/2., C/3., D/1., F/1., H/2.", 
            "PEXZ1E, A/1., B/1., C/3., D/3., F/2., H/2.", "PF2YKK, A/3., B/1., C/1., D/2., F/1., H/2.", "PLQFPN, A/3., B/2., C/1., D/3., F/2., H/1.", 
            "PQWR5B, A/3., B/2., C/1., D/1., F/2., H/1.", "PST8RA, A/3., B/2., C/2., D/1., F/2., H/2.", "PZ20TK, A/2., B/1., C/1., D/1., F/2., H/3.", 
            "P2LJYA, A/1., B/1., C/1., D/2., F/2., H/2.", "P950GT, A/3., B/2., C/1., D/3., F/2., H/2.", "QEQRMY, A/3., B/2., C/1., D/2., F/1., H/2.", 
            "QGSI2B, A/3., B/2., C/1., D/3., F/1., H/1.", "QI198X, A/1., B/1., C/2., D/2., F/2., H/1.", "QJ6007, A/1., B/2., C/3., D/1., F/1., H/2.", 
            "Q1D5GO, A/3., B/1., C/1., D/3., F/1., H/1.", "Q14H22, A/3., B/1., C/3., D/1., F/2., H/1.", "RASWIQ, A/1., B/2., C/3., D/2., F/2., H/3.", 
            "RDE3CS, A/2., B/2., C/1., D/1., F/2., H/2.", "RHVBKN, A/1., B/1., C/2., D/3., F/1., H/3.", "RMXRFG, A/3., B/2., C/1., D/3., F/2., H/3.", 
            "RNBJ4X, A/1., B/1., C/3., D/3., F/2., H/2.", "R532OV, A/2., B/1., C/1., D/3., F/1., H/1.", "SA0MPZ, A/3., B/2., C/1., D/2., F/1., H/1.", 
            "SN20U1, A/3., B/2., C/3., D/1., F/1., H/2.", "S6HQD2, A/3., B/2., C/3., D/2., F/2., H/1.", "TB9FOP, A/3., B/2., C/2., D/1., F/1., H/1.", 
            "T3PUZR, A/1., B/2., C/1., D/2., F/2., H/1.", "T6WVH6, A/2., B/1., C/2., D/2., F/2., H/1.", "T9NQAI, A/3., B/2., C/3., D/2., F/1., H/1.", 
            "U0815G, A/2., B/1., C/1., D/3., F/1., H/3.", "VDN8WH, A/3., B/2., C/2., D/1., F/1., H/2.", "VWD1ZR, A/1., B/2., C/2., D/1., F/2., H/1.", 
            "V4ASUI, A/1., B/2., C/1., D/3., F/2., H/3.", "WKC5V4, A/3., B/1., C/1., D/3., F/2., H/1.", "WLIR82, A/3., B/2., C/3., D/2., F/1., H/1.", 
            "WW5YY3, A/1., B/2., C/1., D/3., F/1., H/3.", "W1IGER, A/2., B/1., C/1., D/1., F/1., H/2.", "XG8ZJ9, A/2., B/1., C/3., D/1., F/1., H/2.", 
            "XK2G4R, A/2., B/1., C/3., D/2., F/2., H/2.", "XN661O, A/3., B/1., C/2., D/3., F/2., H/3.", "XP2D8L, A/3., B/1., C/2., D/1., F/2., H/3.", 
            "XQ3QM8, A/3., B/2., C/3., D/2., F/1., H/2.", "XWAGNC, A/1., B/2., C/3., D/3., F/2., H/3.", "X2ZA3U, A/1., B/1., C/1., D/2., F/1., H/1.", 
            "X3F10S, A/3., B/1., C/2., D/2., F/2., H/1.", "YCY3LB, A/2., B/2., C/1., D/2., F/2., H/1.", "YDI2TP, A/1., B/1., C/3., D/1., F/1., H/1.", 
            "YJA6RK, A/1., B/1., C/3., D/2., F/1., H/3.", "YLCD29, A/1., B/2., C/3., D/3., F/2., H/2.", "YO0D0V, A/1., B/1., C/2., D/1., F/1., H/1.", 
            "Y8TD56, A/1., B/2., C/3., D/3., F/1., H/1.", "ZBDLRL, A/3., B/1., C/3., D/3., F/1., H/3.", "ZELLN3, A/2., B/1., C/2., D/3., F/2., H/3.", 
            "ZFQWVT, A/2., B/1., C/3., D/2., F/2., H/1.", "ZJSZQ2, A/2., B/2., C/3., D/3., F/2., H/2.", "Z3QVU3, A/2., B/1., C/3., D/1., F/1., H/1.", 
            "Z4PRN0, A/1., B/2., C/1., D/2., F/1., H/3.", "Z4WB8E, A/1., B/1., C/3., D/2., F/2., H/1."]

TASK_DATA = {'A_urls': {1: 'https://nipgnas1.inf.elte.hu/~vavsaai@nipg.lab/annbsc23_p1_hw2/qsar_fish_toxicity_noisy.csv',
                        2: 'https://nipgnas1.inf.elte.hu/~vavsaai@nipg.lab/annbsc23_p1_hw2/student-mat_prep_noisy.csv',
                        3: 'https://nipgnas1.inf.elte.hu/~vavsaai@nipg.lab/annbsc23_p1_hw2/student-por_prep_noisy.csv'},
             'A_shapes_orig': {1:(908, 6), 2:(395, 32), 3:(649, 32)},
             'A_nancounts': {1: 388, 2: 329, 3: 469},
             'A_nanpos20': {1: [42, 1], 2: [35, 9], 3: [21, 8]},
             'A_nanpos50': {1: [101, 2], 2: [65, 9], 3: [74, 9]},
             'A_names': {1:"fish-toxicity", 2:"SP-math", 3:"SP-portugal"},
             'B': {1: 'median', 2: 'new_vars'},
             'C': {1: 0.7, 2: 0.6, 3: 0.5},
             'D': {1: 'd50relu_dp03', 2: 'd20relu_dp02_d20relu_dp02_d10relu_dp02', 3: 'd50tanh_d30relu'},
             'F': {1: 3, 2: 4},
             'H': {1: 'd50relu_dp03', 2: 'd20relu_dp02_d20relu_dp02_d10relu_dp02', 3: 'd50tanh_d30relu'}}


class Tester:

    '''
    Member fields:

        TESTS_DICT: dict{test_name - str: test function - Callable}

        neptun_code: str; letter characters converted to capital
        student_tasks: dict{task_name - str: task_id - int}
        dataset_content: None OR str; dataset loaded into a string

        # STORED DATA FROM PREVIOUS TESTS

        features: ndarray; Set in __test_dataset_shape()
        labels: ndarray; Set in __test_dataset_shape()

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
        
        self.TESTS_DICT = {'dataset_load': self.__test_dataset_load,
              'dataset_fill_missing': self.__test_dataset_fill_missing,
              'dataset_split': self.__test_dataset_split,
              'reg_model_architecture': self.__test_reg_model_architecture,
              'reg_model_learning': self.__test_reg_model_learning,
              'cl_dataset': self.__test_cl_dataset,
              'cl_onehot': self.__test_cl_onehot,
              'cl_model_architecture': self.__test_cl_model_architecture,
              'cl_model_learning': self.__test_cl_model_learning}

        self.dataset_content = None
        self.features = None
        self.labels = None
        self.test_results = {k: False for k in self.TESTS_DICT.keys()}

        if debug_mode:
            assert type(neptun_code) == dict
            assert len(neptun_code) == N_TASKS
            self.student_tasks = neptun_code
        else:
            self.neptun_code = neptun_code.strip().upper()
            self.__get_student_tasks()


    def get_dataset_content(self):
        '''
        Sets self.dataset_content.
        Returns:
            dataset_content: str
        '''
        if self.dataset_content is None:
            url = TASK_DATA['A_urls'][self.student_tasks['A']]
            ftpstream = urllib.request.urlopen(url)
            self.dataset_content = ftpstream.read().decode('utf-8')
        return self.dataset_content

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
            assert all([len(word) == 4 for word in words[1:]]), "Tester error: Invalid task format: " + str(words)
            self.student_tasks = {word[0]: int(word[-2]) for word in words[1:]}
            return
        # neptun code not found
        assert False, "Tester: Neptun code was not found in the student list: " + str(self.neptun_code)

    # TESTS

    def __test_dataset_load(self, *args):
        '''
        Expected parameters:
            features_noisy: ndarray(n_samples, n_features) of float32
            labels: ndarray(n_samples,) of float32
        '''
        assert len(args) == 2, "Tester error: __test_dataset_load() expects 2 parameters: features_noisy, labels. "
        features_noisy, labels = args

        # test features_noisy, labels array type & shape
        assert type(features_noisy) == np.ndarray and type(labels) == np.ndarray, "Tester: features_noisy and labels both must be numpy arrays."
        assert features_noisy.dtype == np.float32 and labels.dtype == np.float32, "Tester: features_noisy and labels both must have float32 dtype."
        expected_shape = TASK_DATA['A_shapes_orig'][self.student_tasks['A']]
        assert features_noisy.shape == expected_shape, "Tester: features_noisy array shape should be " + str(expected_shape)
        assert labels.shape == features_noisy.shape[:1], "Tester: labels array must have (n_samples,) shape."

        # check NaN counts and positions in features_noisy array
        nancount = TASK_DATA['A_nancounts'][self.student_tasks['A']]
        nanpos20 = TASK_DATA['A_nanpos20'][self.student_tasks['A']]
        nanpos50 = TASK_DATA['A_nanpos50'][self.student_tasks['A']]

        nanmask = np.isnan(features_noisy)
        nanidxs = np.argwhere(nanmask)
        assert np.count_nonzero(nanmask) == nancount, "Tester: incorrect NaN count in 'features_noisy' array."
        assert np.count_nonzero(np.isnan(labels)) == 0, "Tester: There should be no NaN values in 'labels' array."
        assert np.all(nanidxs[20] == nanpos20), "Tester: incorrect NaN value positions in 'features_noisy' array."
        assert np.all(nanidxs[50] == nanpos50), "Tester: incorrect NaN value positions in 'features_noisy' array."

        self.labels = np.copy(labels)

        print("Tester: Dataset loading OK")

    def __test_dataset_fill_missing(self, *args):
        '''
        Expected parameters:
            features: ndarray(n_samples, n_features) of float32
        '''
        assert len(args) == 1, "Tester error: __test_dataset_fill_missing() expects 1 parameters: features. "
        features, = args

        # test features array type & shape
        assert type(features) == np.ndarray, "Tester: features must be numpy array."
        assert features.dtype == np.float32, "Tester: features array must have float32 dtype."
        orig_shape = TASK_DATA['A_shapes_orig'][self.student_tasks['A']]

        # test correct fill of missing data and/or new variables
        assert not np.any(np.isnan(features)), "Tester: no NaN values should be present in the features array."
        fill_method = TASK_DATA['B'][self.student_tasks['B']]
        if fill_method == 'median':
            assert features.shape == orig_shape, "Tester: features array shape should be " + str(orig_shape)        
            nanpos20 = tuple(TASK_DATA['A_nanpos20'][self.student_tasks['A']])
            nanpos50 = tuple(TASK_DATA['A_nanpos50'][self.student_tasks['A']])
            nanpos20_median = {1: 0.58, 2: 3., 3: 2.}[self.student_tasks['A']]
            nanpos50_median = {1: 1.225, 2: 3., 3: 2.}[self.student_tasks['A']]
            assert np.allclose(features[nanpos20], nanpos20_median)
            assert np.allclose(features[nanpos50], nanpos50_median)

        elif fill_method == 'new_vars':
            n_new_vars_task_A = {1: 2, 2: 4, 3: 4}[self.student_tasks['A']]
            new_shape = (orig_shape[0], orig_shape[1] + n_new_vars_task_A)
            assert features.shape == new_shape, "Tester: features array shape should be " + str(new_shape)
            new_vars = features[:,-n_new_vars_task_A:]
            new_vars_size = features[:,-n_new_vars_task_A:].size
            assert new_vars_size - np.sum(new_vars) == TASK_DATA['A_nancounts'][self.student_tasks['A']], "Tester: incorrect sum of elements in new variable columns of the features array."
            u_new_var_values = np.unique(new_vars)
            assert u_new_var_values.shape[0] == 2, "Tester: incorrect values in new variable columns of the features array."
            assert np.all(u_new_var_values == [0,1]), "Tester: incorrect values in new variable columns of the features array."
        else:
            assert False, "Tester error: __test_dataset_fill_missing() invalid fill_method name: " \
                                                                        + str(fill_method)

        # storing data for later use
        self.features = np.copy(features)

        print("Tester: Dataset loading OK")

    def __test_dataset_split(self, *args):
        '''
        Expected parameters:
            x_train, x_val, x_test: ndarray(n_split_samples, n_features) of float32
            y_train, y_val, y_test: ndarray(n_split_samples,) of float32
        '''
        assert len(args) == 6, "Tester error: __test_dataset_split() expects 6 parameters: " +\
                                    "x_train, x_val, x_test, y_train, y_val, y_test. "
        assert self.features is not None and self.labels is not None, "Tester error: Run tester for task 'A' & 'B' first."

        # test split array types, shapes
        assert all([type(a) == np.ndarray for a in args]), "Tester: all split arrays must be numpy arrays."
        x_train, x_val, x_test, y_train, y_val, y_test = args
        expected_shape = self.features.shape
        assert all(a.shape[1] == expected_shape[1] for a in [x_train, x_val, x_test]), "Tester: split feature array " +\
                                                    "shape should be (?," + str(expected_shape[1]) + ")."
        assert all([ax.shape[0] == ay.shape[0] for ax, ay in zip([x_train, x_val, x_test], [y_train, y_val, y_test])]), \
                                                    "Tester: shape of x and y splits must match along axis#0. "
        x_concat = np.concatenate([x_train, x_val, x_test], axis=0)
        y_concat = np.concatenate([y_train, y_val, y_test], axis=0)
        assert x_concat.shape == expected_shape, "Tester: concatenated x splits do not match original features array shape."
        assert y_concat.shape == expected_shape[:1], "Tester: concatenated y splits do not match original labels array shape."
        split_train_ratio = TASK_DATA['C'][self.student_tasks['C']]

        n_train_samples = int(expected_shape[0]*split_train_ratio)
        n_valtest_samples = int(expected_shape[0]*(1.-split_train_ratio)*0.5)
        assert abs(x_train.shape[0] - n_train_samples) <= 2, "Tester: Train split ratio must be " + str(split_train_ratio)
        assert abs(x_val.shape[0] - n_valtest_samples) <= 2, "Tester: Vaidation split ratio must be " + str(n_valtest_samples)
        assert abs(x_test.shape[0] - n_valtest_samples) <= 2, "Tester: Test split ratio must be " + str(n_valtest_samples)

        # test if shuffled
        assert np.any(x_concat != self.features), "Tester: features and labels array must be shuffled before split. "

        # test if shuffle was consistent
        u_pairs_before = np.unique(np.concatenate([self.features, self.labels[:,None]], axis=-1), axis=0)
        u_pairs_after = np.unique(np.concatenate([x_concat, y_concat[:,None]], axis=-1), axis=0)
        assert np.array_equal(u_pairs_before, u_pairs_after), "Tester: the features and labels array were shuffled with different permutations."

        print("Tester: Dataset split OK")

    def __test_reg_model_architecture(self, *args):
        '''
        Expected parameters:
            reg_model: keras Model
        '''
        assert len(args) == 1, "Tester error: __test_reg_model_architecture() expects 1 parameter: reg_model "
        
        model_architecture_name = TASK_DATA['D'][self.student_tasks['D']]
        reg_model, = args

        assert isinstance(reg_model, tf.keras.models.Sequential), "Tester: In this assignment you must use the Sequential model (tf.keras version)"
        assert reg_model._is_compiled, "Tester: The model must be compiled."
        assert 'mse' in str(reg_model.loss) or 'mean_squared_error' in str(reg_model.loss), "Tester: Incorrect regression loss."

        if model_architecture_name == 'd50relu_dp03':
            assert len(reg_model.layers) == 3, "Tester: In your task, the network should have exactly 3 layers (dropout included)."
            assert isinstance(reg_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(reg_model.layers[1], tf.keras.layers.Dropout), "Tester: Layer#1 should be a Dropout layer."
            assert isinstance(reg_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert reg_model.layers[0].units == 50, "Tester: Layer#0 should have 50 neurons."
            assert reg_model.layers[2].units == 1,  "Tester: Incorrect number of neurons in Layer#2 (should be last layer)."
            assert reg_model.layers[0].activation == tf.keras.activations.relu, "Tester: Layer#0 should have a ReLU activation function."
            assert reg_model.layers[2].activation == tf.keras.activations.linear, "Tester: Incorrect activation function in Layer#2 (should be last layer)."
            assert abs(reg_model.layers[1].rate - .3) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.3."

        elif model_architecture_name == 'd20relu_dp02_d20relu_dp02_d10relu_dp02':
            assert len(reg_model.layers) == 7, "Tester: In your task, the network should have exactly 7 layers (dropout included)."
            assert isinstance(reg_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(reg_model.layers[1], tf.keras.layers.Dropout), "Tester: Layer#1 should be a Dropout layer."
            assert isinstance(reg_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert isinstance(reg_model.layers[3], tf.keras.layers.Dropout), "Tester: Layer#3 should be a Dropout layer."
            assert isinstance(reg_model.layers[4], tf.keras.layers.Dense), "Tester: Layer#4 should be a Dense layer."
            assert isinstance(reg_model.layers[5], tf.keras.layers.Dropout), "Tester: Layer#5 should be a Dropout layer."
            assert isinstance(reg_model.layers[6], tf.keras.layers.Dense), "Tester: Layer#6 should be a Dense layer."
            assert reg_model.layers[0].units == 20, "Tester: Layer#0 should have 20 neurons."
            assert reg_model.layers[2].units == 20, "Tester: Layer#2 should have 20 neurons."
            assert reg_model.layers[4].units == 10, "Tester: Layer#4 should have 10 neurons."
            assert reg_model.layers[6].units == 1, "Tester: Incorrect number of neurons in Layer#6 (should be last layer)."
            assert reg_model.layers[0].activation == tf.keras.activations.relu, "Tester: Layer#0 should have a ReLU activation function."
            assert reg_model.layers[2].activation == tf.keras.activations.relu, "Tester: Layer#2 should have a ReLU activation function."
            assert reg_model.layers[4].activation == tf.keras.activations.relu, "Tester: Layer#4 should have a ReLU activation function."
            assert reg_model.layers[6].activation == tf.keras.activations.linear, "Tester: Incorrect activation function in Layer#6 (should be last layer)."
            assert abs(reg_model.layers[1].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."
            assert abs(reg_model.layers[3].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."
            assert abs(reg_model.layers[5].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."

        elif model_architecture_name == 'd50tanh_d30relu':
            assert len(reg_model.layers) == 3, "Tester: In your task, the network should have exactly 3 layers."
            assert isinstance(reg_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(reg_model.layers[1], tf.keras.layers.Dense), "Tester: Layer#1 should be a Dense layer."
            assert isinstance(reg_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert reg_model.layers[0].units == 50, "Tester: Layer#0 should have 50 neurons."
            assert reg_model.layers[1].units == 30, "Tester: Layer#1 should have 30 neurons."
            assert reg_model.layers[2].units == 1, "Tester: Incorrect number of neurons in Layer#2 (should be last layer)."
            assert reg_model.layers[0].activation == tf.keras.activations.tanh, "Tester: Layer#0 should have a tanh activation function."
            assert reg_model.layers[1].activation == tf.keras.activations.relu, "Tester: Layer#1 should have a ReLU activation function."
            assert reg_model.layers[2].activation == tf.keras.activations.linear, "Tester: Incorrect activation function in Layer#2 (should be last layer)."

        else:
            assert False, "Tester error: __test_reg_model_architecture() invalid model_architecture_name: " \
                                                                        + str(model_architecture_name)

        print("Tester: Regression model architecture OK")


    def __test_reg_model_learning(self, *args):
        '''
        Expected parameters:
            test_mse, test_mae: float
        '''
        assert len(args) == 2, "Tester error: __test_reg_model_learning() expects 2 parameters: test_mse, test_mae "

        dataset_name = TASK_DATA['A_names'][self.student_tasks['A']]
        test_mse, test_mae = args
        min_test_mses = {'fish-toxicity': 0.3,
                         'SP-math': 1.5,
                         'SP-portugal': 0.8}
        max_test_mses = {'fish-toxicity': 1.5,
                         'SP-math': 10.,
                         'SP-portugal': 8.}
        min_test_maes = {'fish-toxicity': 0.6,
                         'SP-math': 0.5,
                         'SP-portugal': 0.5}
        max_test_maes = {'fish-toxicity': 1,
                         'SP-math': 3.,
                         'SP-portugal': 2.}
        assert dataset_name in min_test_mses.keys(), "Tester error: __test_reg_model_learning() invalid dataset_name: "\
                                                                 + str(dataset_name)
        assert test_mse > min_test_mses[dataset_name] and test_mse < max_test_mses[dataset_name], "Tester: A well-trained model "+\
                    "should produce an MSE between " + str(min_test_mses[dataset_name]) + " and " + str(max_test_mses[dataset_name])
        assert test_mae > min_test_maes[dataset_name] and test_mae < max_test_maes[dataset_name], "Tester: A well-trained model "+\
                    "should produce a MAE between " + str(min_test_maes[dataset_name]) + " and " + str(max_test_maes[dataset_name])

        print("Tester: Regression model learning OK")


    def __test_cl_dataset(self, *args):
        '''
        Expected parameters:
            y_cat_train, y_cat_val, y_cat_test: ndarray(n_split_samples) of int
        '''
        assert len(args) == 3, "Tester error: __test_cl_dataset() expects 3 parameters: y_cat_train, y_cat_val, y_cat_test "

        num_classes = TASK_DATA['F'][self.student_tasks['F']]

        # test shapes
        y_cat_train, y_cat_val, y_cat_test = args
        y_cat_concat = np.concatenate([y_cat_train, y_cat_val, y_cat_test], axis=0)
        assert y_cat_concat.shape == self.labels.shape, "Tester: concatenated y_cat splits do not match original label array shape."
        assert len(np.unique(y_cat_concat)) == num_classes, "Tester: there should be {:d} categories".format(num_classes)
        # test contents: label distribution should be _approximately_ equal
        for y_cat_split, y_cat_split_name in zip([y_cat_train, y_cat_val, y_cat_test], ["y_cat_train", "y_cat_val", "y_cat_test"]):
            u_y_cat_split, c_y_cat_split = np.unique(y_cat_split, return_counts=True)
            assert np.array_equal(u_y_cat_split, np.arange(num_classes)), "Tester: not all label categories are present in " + str(y_cat_split_name)
            min_c_y_cat_split = np.amin(c_y_cat_split)
            max_c_y_cat_split = np.amax(c_y_cat_split)
            assert min_c_y_cat_split*4. > max_c_y_cat_split, "Tester: number of samples from each label category"+\
                            " should be _approximately_ equal; this is not the case in " + y_cat_split_name

        print("Tester: Classification dataset creation OK")

    def __test_cl_onehot(self, *args):
        '''
        Expected parameters:
            y_onehot_train, y_onehot_val, y_onehot_test: ndarray(n_split_samples, n_categories) of int
        '''
        assert len(args) == 3, "Tester error: __test_cl_onehot() expects 3 parameters: "+\
                                            "y_onehot_train, y_onehot_val, y_onehot_test "

        num_classes = TASK_DATA['F'][self.student_tasks['F']]

        y_onehot_train, y_onehot_val, y_onehot_test = args
        y_onehot_concat = np.concatenate([y_onehot_train, y_onehot_val, y_onehot_test], axis=0)
        assert y_onehot_concat.shape[:1] == self.labels.shape, "Tester: concatenated y_onehot splits do not match original label array shape."
        assert y_onehot_concat.shape[1:] == (num_classes,), "Tester: y_onehot splits should have a shape: (n_samples, {:d})".format(num_classes)

        assert np.all(np.sum(y_onehot_concat, axis=1) == 1.), "Tester: y_onehot vectors must have a sum of 1"
        assert np.all(np.count_nonzero(y_onehot_concat, axis=1) == 1), "Tester: y_onehot vectors must have a single non-zero item"
        
        for y_onehot_split, y_onehot_split_name in zip([y_onehot_train, y_onehot_val, y_onehot_test],\
                                                       ["y_onehot_train", "y_onehot_val", "y_onehot_test"]):
            y_cat_split = np.argmax(y_onehot_split, axis=1)
            u_y_cat_split, c_y_cat_split = np.unique(y_cat_split, return_counts=True)
            assert np.array_equal(u_y_cat_split, np.arange(num_classes)), "Tester: not all label categories are present in " + str(y_onehot_split_name)
            min_c_y_cat_split = np.amin(c_y_cat_split)
            max_c_y_cat_split = np.amax(c_y_cat_split)
            assert min_c_y_cat_split*4. > max_c_y_cat_split, "Tester: number of samples from each label category"+\
                            " should be _approximately_ equal; this is not the case in " + y_onehot_split_name

        print("Tester: One-hot conversion OK")

    def __test_cl_model_architecture(self, *args):
        '''
        Expected parameters:
            cl_model: keras.models.Sequential() instance
        '''
        assert len(args) == 1, "Tester error: __test_cl_model_architecture() expects 1 parameter: cl_model "


        model_architecture_name = TASK_DATA['H'][self.student_tasks['H']]
        num_classes = TASK_DATA['F'][self.student_tasks['F']]
        cl_model, = args


        assert isinstance(cl_model, tf.keras.models.Sequential), "Tester: In this assignment you must use the Sequential model (tf.keras version)"
        assert cl_model._is_compiled, "Tester: The model must be compiled."
        assert 'categorical_crossentropy' in str(cl_model.loss), "Tester: Incorrect multi-class classification loss."

        if model_architecture_name == 'd50relu_dp03':
            assert len(cl_model.layers) == 3, "Tester: In your task, the network should have exactly 3 layers."
            assert isinstance(cl_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(cl_model.layers[1], tf.keras.layers.Dropout), "Tester: Layer#1 should be a Dropout layer."
            assert isinstance(cl_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert cl_model.layers[0].units == 50, "Tester: Layer#0 should have 50 neurons."
            assert cl_model.layers[2].units == num_classes, "Tester: Incorrect number of neurons in Layer#2 (should be last layer)."
            assert cl_model.layers[0].activation == tf.keras.activations.relu, "Tester: Layer#0 should have a ReLU activation function."
            assert cl_model.layers[2].activation == tf.keras.activations.softmax, "Tester: Incorrect activation function in Layer#2 (should be last layer)."
            assert abs(cl_model.layers[1].rate - .3) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.3."

        elif model_architecture_name == 'd20relu_dp02_d20relu_dp02_d10relu_dp02':
            assert len(cl_model.layers) == 7, "Tester: In your task, the network should have exactly 7 layers."
            assert isinstance(cl_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(cl_model.layers[1], tf.keras.layers.Dropout), "Tester: Layer#1 should be a Dropout layer."
            assert isinstance(cl_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert isinstance(cl_model.layers[3], tf.keras.layers.Dropout), "Tester: Layer#3 should be a Dropout layer."
            assert isinstance(cl_model.layers[4], tf.keras.layers.Dense), "Tester: Layer#4 should be a Dense layer."
            assert isinstance(cl_model.layers[5], tf.keras.layers.Dropout), "Tester: Layer#5 should be a Dropout layer."
            assert isinstance(cl_model.layers[6], tf.keras.layers.Dense), "Tester: Layer#6 should be a Dense layer."
            assert cl_model.layers[0].units == 20, "Tester: Layer#0 should have 20 neurons."
            assert cl_model.layers[2].units == 20, "Tester: Layer#2 should have 20 neurons."
            assert cl_model.layers[4].units == 10, "Tester: Layer#4 should have 10 neurons."
            assert cl_model.layers[6].units == num_classes, "Tester: Incorrect number of neurons in Layer#6 (should be last layer)."
            assert cl_model.layers[0].activation == tf.keras.activations.relu, "Tester: Layer#0 should have a ReLU activation function."
            assert cl_model.layers[2].activation == tf.keras.activations.relu, "Tester: Layer#2 should have a ReLU activation function."
            assert cl_model.layers[4].activation == tf.keras.activations.relu, "Tester: Layer#4 should have a ReLU activation function."
            assert cl_model.layers[6].activation == tf.keras.activations.softmax, "Tester: Incorrect activation function in Layer#6 (should be last layer)."
            assert abs(cl_model.layers[1].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."
            assert abs(cl_model.layers[3].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."
            assert abs(cl_model.layers[5].rate - .2) < 0.001, "Tester: Dropout layer should have a dropout rate of 0.2."

        elif model_architecture_name == 'd50tanh_d30relu':
            assert len(cl_model.layers) == 3, "Tester: In your task, the network should have exactly 3 layers."
            assert isinstance(cl_model.layers[0], tf.keras.layers.Dense), "Tester: Layer#0 should be a Dense layer."
            assert isinstance(cl_model.layers[1], tf.keras.layers.Dense), "Tester: Layer#1 should be a Dense layer."
            assert isinstance(cl_model.layers[2], tf.keras.layers.Dense), "Tester: Layer#2 should be a Dense layer."
            assert cl_model.layers[0].units == 50, "Tester: Layer#0 should have 50 neurons."
            assert cl_model.layers[1].units == 30, "Tester: Layer#1 should have 30 neurons."
            assert cl_model.layers[2].units == num_classes, "Tester: Incorrect number of neurons in Layer#2 (should be last layer)."
            assert cl_model.layers[0].activation == tf.keras.activations.tanh, "Tester: Layer#0 should have a tanh activation function."
            assert cl_model.layers[1].activation == tf.keras.activations.relu, "Tester: Layer#1 should have a ReLU activation function."
            assert cl_model.layers[2].activation == tf.keras.activations.softmax, "Tester: Incorrect activation function in Layer#2 (should be last layer)."

        else:
            assert False, "Tester error: __test_cl_model_architecture() invalid model_architecture_name: " \
                                                                        + str(model_architecture_name)

        print("Tester: Classification model architecture OK")


    def __test_cl_model_learning(self, *args):
        '''
        Expected parameters:
            test_ce, test_acc: float
        '''
        assert len(args) == 2, "Tester error: __test_cl_model_learning() expects 2 parameters:" +\
                                             " test_ce, test_acc"

        dataset_name = TASK_DATA['A_names'][self.student_tasks['A']]
        num_classes = TASK_DATA['F'][self.student_tasks['F']]

        test_ce, test_acc = args
        min_test_ces = {'fish-toxicity': {3: 0.6, 4: 0.8},
                         'SP-math': {3: 0.3, 4: 0.3},
                         'SP-portugal': {3: 0.3, 4: 0.3},
                         'SP-math-nograde': {3: 0.8, 4: 0.8},
                         'SP-portugal-nograde': {3: 0.6, 4: 0.6},
                         'CCS': {3: 0.2, 4: 0.2}}
        max_test_ces = {'fish-toxicity': {3: 1.1, 4: 1.25},
                         'SP-math': {3: 0.9, 4: 1.25},
                         'SP-portugal': {3: 0.8, 4: 1.2},
                         'SP-math-nograde': {3: 1.4, 4: 1.45},
                         'SP-portugal-nograde': {3: 1.25, 4: 1.35},
                         'CCS': {3: 0.8, 4: 1.15}}
        min_test_accs = {'fish-toxicity': {3: 0.5, 4: 0.4},
                         'SP-math': {3: 0.6, 4: 0.4},
                         'SP-portugal': {3: 0.65, 4: 0.45},
                         'SP-math-nograde': {3: 0.33, 4: 0.25},
                         'SP-portugal-nograde': {3: 0.4, 4: 0.3},
                         'CCS': {3: 0.65, 4: 0.4}}
        max_test_accs = {'fish-toxicity': {3: 0.75, 4: 0.8},
                         'SP-math': {3: 0.9, 4: 0.9},
                         'SP-portugal': {3: 0.9, 4: 0.9},
                         'SP-math-nograde': {3: 0.6, 4: 0.6},
                         'SP-portugal-nograde': {3: 0.75, 4: 0.7},
                         'CCS': {3: 0.95, 4: 0.95}}

        assert dataset_name in min_test_ces.keys(), "Tester error: __test_cl_model_learning() invalid dataset_name: "\
                                                                 + str(dataset_name)

        min_test_ce, max_test_ce = min_test_ces[dataset_name][num_classes], max_test_ces[dataset_name][num_classes]
        assert test_ce > min_test_ce and test_ce < max_test_ce, "Tester: A well-trained model should produce a CE loss between " \
                                                                + str(min_test_ce) + " and " + str(max_test_ce)

        min_test_acc, max_test_acc = min_test_accs[dataset_name][num_classes], max_test_accs[dataset_name][num_classes]
        assert test_acc > min_test_acc and test_acc < max_test_acc, "Tester: A well-trained model should produce accuracy between " \
                                                                    + str(min_test_acc) + " and " + str(max_test_acc)
        print("Tester: Classification model learning OK")