import unittest
import numpy as np

def false_discovery_rate(class_preds, class_labels) -> float:
    unique_labels = np.unique(class_labels)
    correct_labels = np.argmax(class_preds, axis=1)

    class_labels = np.tile(class_labels, (unique_labels.size ,1)) 
    correct_labels = np.tile(correct_labels, (unique_labels.size ,1)) 

    p_mask = class_labels == unique_labels.reshape((unique_labels.size, 1))
    ap = correct_labels == unique_labels.reshape((unique_labels.size, 1))
    vp = np.logical_and(p_mask, ap)

    fdrs = 1 - (np.sum(vp, axis=1) / np.sum(ap, axis=1))
    return np.mean(fdrs, axis=0)

class TestFDR(unittest.TestCase):

    def test_two_classes(self):
        two_class_preds = np.array([[0.4, 0.6], [0.8, 0.2], [0.55, 0.45], [0.1, 0.9]])  # [1,0,0,1]
        two_class_labels = np.array([0,0,1,1])
        self.assertAlmostEqual(false_discovery_rate(two_class_preds, two_class_labels), 1./2.)

    def test_three_classes(self):
        three_class_preds = np.array([[0.4, 0.3, 0.3], [0.1, 0.5, 0.4], 
                                     [0.3, 0.2, 0.5], [0.4, 0.25, 0.35]])  # [0,1,2,0]
        three_class_labels = np.array([0, 1, 2, 2])
        self.assertAlmostEqual(false_discovery_rate(three_class_preds, three_class_labels), 1./6.)

    def test_four_classes(self):
        four_class_preds = np.array([[1., 0., 0., 0.], [1., 0., 0., 0.], 
                                     [0., 0., 1., 0.], [0., 0., 1., 0.],
                                     [0., 1., 0., 0.], [0., 0., 0., 1.],
                                     ])  # [0,0,2,2,1,3]
        four_class_labels = np.array([0, 2, 1, 1, 1, 3])
        self.assertAlmostEqual(false_discovery_rate(four_class_preds, four_class_labels), 3./8.)

def suite():
    suite = unittest.TestSuite()
    testfuns = ["test_two_classes", "test_three_classes", "test_four_classes"]
    [suite.addTest(TestFDR(fun)) for fun in testfuns]
    return suite

runner = unittest.TextTestRunner(verbosity=2)
runner.run(suite())
