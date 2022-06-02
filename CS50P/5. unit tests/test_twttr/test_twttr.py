from twttr import shorten

def test_lowercase():
    test_strings = {"a": "", "aa":"", "aeiou": "", "baboon": "bbn", "styl": "styl"}
    for key in test_strings:
        assert shorten(key) == test_strings[key]

def test_allcase():
    test_strings = {"A": "", "AA":"", "AeIoU": "", "BabOoN": "BbN", "styL": "styL"}
    for key in test_strings:
        assert shorten(key) == test_strings[key]

def test_nonstring():
    test_strings = {"123": "123", "\n":"\n", "!?.\")(*&@^%$!@*#_!)": "!?.\")(*&@^%$!@*#_!)"}
    for key in test_strings:
        assert shorten(key) == test_strings[key]