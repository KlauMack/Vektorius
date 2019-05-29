# Vektoriaus klasė

## Įdiegimas (Unix kompiuteryje) naudojant `gcc`kompiliatorių 

- `git clone https://github.com/KlauMack/Vektorius.git`
- `cd Vektorius`
- `make`
- `./vector`

## Efektyvumo/spartos analizė

|  Vektorius  |    10000    |    100000   |   1000000   |  10000000  | 100000000 |
| ----------- | ----------- | ----------- | ----------- | ---------- | --------- |
| std::vector | 0.0002444 s | 0.0027946 s | 0.0197756 s | 0.210041 s | 1.93072 s |
|    Vector   | 0.0002489 s | 0.0020631 s | 0.0207604 s | 0.223814 s | 2.01185 s |

## Perskirstymas

|  Vektorius  | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| ----------- | ----- | ------ | ------- | -------- | --------- |
| std::vector |   14  |   17   |    20   |    24    |     27    |
|    Vector   |   14  |   17   |    20   |    24    |     27    |

## Funkcijos, kurios dar nėra realizuotos
- **member functions**
```shell
    vector::assign fill version
	vector::assign range version
	vector::assign initializer list version
    vector::data
	vector::emplace
	vector::emplace_back
    vector::erase position version
	vector::erase range version
    vector::get_allocator
	vector::insert single element version
	vector::insert fill version
	vector::insert range version
	vector::insert move version
	vector::insert initializer list version
	vector::max_size
    vector::operator = initializer list version
    vector::swap
```
- **non-member overloaded functions**
```shell
    operator ==
    operator !=
	operator <
	operator <=
	operator >
	operator >=
	swap
```