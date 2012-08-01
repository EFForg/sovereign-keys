#!/usr/bin/env python
"""Test cases for the SK module which wraps libsk for use from Python."""

import unittest
import os
import sys

# Reference the generated sk.py.
sys.path.extend([os.path.join(sys.path[0], d)
                 for d in ('../build', '../build/libsk')])
import sk


class MessageTestCase(unittest.TestCase):
    """Tests the Message wrapper class."""

    def testTextSerialization_Sanity(self):
        text = ''.join([
            'Add-Root-CA: 1\n',
            'CA-Cert: Li4u\n',
            'SN: 42\n',
            'Signature: Li4u\n',
            'TID: 0\n',
            'Timestamp: 1342885825\n',
            '\n'])
        message = sk.Message.parse_text(text)
        self.assertIsNotNone(message)
        self.assertEqual(text, message.write_text())

    def testTextParseError(self):
        with self.assertRaises(ValueError):
            _ = sk.Message.parse_text('bogus')

    def testBinarySerialization_Sanity(self):
        # Note this message contains an embedded NUL to test for C string
        # termination issues.
        data = ("\x07\x01\x03\x2e\x2e\x2e\x2a\x03\x2e\x2e\x2e\x00"
                "\xc1\xcf\x0a\x50")
        message, size = sk.Message.parse_binary(data)
        self.assertIsNotNone(message)
        self.assertEqual(len(data), size)
        self.assertEqual(data, message.write_binary())

    def testParseBinaryError(self):
        with self.assertRaises(ValueError):
            _, _ = sk.Message.parse_binary('bogus')


class TFMTestCase(unittest.TestCase):
    """Tests the TFM wrapper class."""

    text = ''.join([
        'TFM: 1\n'
        'Max-Published-SN: 42\n'
        'Max-Published-Timestamp: 1000\n'
        'Max-SN: 57\n'
        'Max-Timestamp: 1100\n'
        'Signature: Li4u\n'
        'TID: 0\n'
        'Timestamp: 2000\n'
        '\n'])

    def testGetters(self):
        tfm = sk.TFM.parse_text(TFMTestCase.text)
        self.assertEquals(42, tfm.get_max_published_sn())
        self.assertEquals(1000, tfm.get_max_published_timestamp())
        self.assertEquals(57, tfm.get_max_sn())
        self.assertEquals(1100, tfm.get_max_timestamp())
        self.assertEquals('...', tfm.get_signature())
        self.assertEquals(0, tfm.get_tid())
        self.assertEquals(2000, tfm.get_timestamp())

    def testSetters(self):
        tfm = sk.TFM(1)
        tfm.set_max_published_sn(42)
        tfm.set_max_published_timestamp(1000)
        tfm.set_max_sn(57)
        tfm.set_max_timestamp(1100)
        tfm.set_signature('...')
        tfm.set_tid(0)
        tfm.set_timestamp(2000)
        self.assertEquals(TFMTestCase.text, tfm.write_text())


if __name__ == '__main__':
    unittest.main()
