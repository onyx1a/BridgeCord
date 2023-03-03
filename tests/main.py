import sys
import pytest
import bridgecord as bc


def test_main():
    assert bc.TestBridge() == "Make Bridge!"
