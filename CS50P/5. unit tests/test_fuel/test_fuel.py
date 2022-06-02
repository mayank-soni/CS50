from fuel import convert, gauge
from pytest import raises

def test_convert():
    assert convert("1/2")==50
    with raises(ZeroDivisionError):
        convert("1/0")
    with raises(ValueError):
        convert("cat/dog")
    with raises(ValueError):
        convert("4/3")
    with raises(ValueError):
        convert("-1/50")

def test_gauge():
    assert gauge(50) == "50%"
    assert gauge(98) == "98%"
    assert gauge(99) == "F"
    assert gauge(0) == "E"
    assert gauge(1) == "E"
    assert gauge(5) == "5%"