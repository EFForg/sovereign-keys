#!/usr/bin/env python

import unittest
import sys
import os

sys.path.extend(['../build', '../build/libsk'])
import sk


class MessageTestCase(unittest.TestCase):
    """Tests the Message wrapper class."""

    def testTextSerialization(self):
        MSG = ''.join([
            'Add-Root-CA: 1\n',
            'CA-Cert: Li4u\n',
            'SN: 42\n',
            'Signature: Li4u\n',
            'TID: 0\n',
            'Timestamp: 1342885825\n',
            '\n'])
        message = sk.Message.ParseText(MSG)
        self.assertIsNotNone(message)
        self.assertEqual(MSG, message.WriteText())

    def testBinarySerialization(self):
        # Note this message contains an embedded NUL.
        MSG = "\x07\x01\x03\x2e\x2e\x2e\x2a\x03\x2e\x2e\x2e\x00\xc1\xcf\x0a\x50"
        message, size = sk.Message.ParseBinary(MSG)
        self.assertIsNotNone(message)
        self.assertEqual(len(MSG), size)
        self.assertEqual(MSG, message.WriteBinary())


if __name__ == '__main__':
    unittest.main()
