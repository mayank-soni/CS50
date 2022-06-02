from bank import value

def test_hello():
    assert value("Hello") == 0
    assert value("Hello Brian") == 0
    assert value("Hellolasmdlqw")== 0

def test_case():
    assert value("hello") == 0
    assert value("heLlO") == 0
    assert value("HELLO") == 0

def test_h():
    assert value("h") == 20
    assert value("hwqkeo") == 20

def test_others():
    assert value("wassdlqw") == 100
    assert value("219310!@#I$OI#>>D>AS??''") == 100
    assert value("") == 100
    assert value("\n") == 100