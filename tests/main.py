import sys
import pytest

@pytest.mark.skipif(sys.platform.startswith("win32"), reason="NYI")
def test_main():
    import discordBridge as dbridge
    assert dbridge.TestBridge() == "Make Bridge!"
