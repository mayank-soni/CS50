from plates import is_valid

def test_length():
    assert is_valid("a") == False
    assert is_valid("abracad") == False

def test_two_letters_at_start():
    assert is_valid("a1") == False

def test_punctuation():
    assert is_valid("aba.") == False

def test_numbers():
    assert is_valid("aba5a") == False
    assert is_valid("aba0") == False