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

    def testBinarySerialization_Sanity(self):
        # Note this message contains an embedded NUL to test for C string
        # termination issues.
        data = ("\x07\x01\x03\x2e\x2e\x2e\x2a\x03\x2e\x2e\x2e\x00"
                "\xc1\xcf\x0a\x50")
        message, size = sk.Message.parse_binary(data)
        self.assertIsNotNone(message)
        self.assertEqual(len(data), size)
        self.assertEqual(data, message.write_binary())


if __name__ == '__main__':
    unittest.main()
