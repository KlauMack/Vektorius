# Vektoriaus klasė

## Įdiegimas (Unix kompiuteryje) naudojant `gcc`kompiliatorių 

- `git clone https://github.com/KlauMack/Vektorius.git`
- `cd Vektorius`
- `make`
- `./vector`

## Efektyvumo/spartos analizė (`<int>`)

|  Vektorius  |    10000    |    100000   |   1000000   |  10000000  | 100000000 |
| ----------- | ----------- | ----------- | ----------- | ---------- | --------- |
| std::vector | 0.0002444 s | 0.0027946 s | 0.0197756 s | 0.210041 s | 1.93072 s |
|    Vector   | 0.0002489 s | 0.0020631 s | 0.0207604 s | 0.223814 s | 2.01185 s |

## Perskirstymas (`<int>`)

|  Vektorius  | 10000 | 100000 | 1000000 | 10000000 | 100000000 |
| ----------- | ----- | ------ | ------- | -------- | --------- |
| std::vector |   14  |   17   |    20   |    24    |     27    |
|    Vector   |   14  |   17   |    20   |    24    |     27    |

## Efektyvumo/spartos analizė (`<Studentas>`)

|  Vektorius  |    10000    |    100000   |   1000000   |  10000000  |
| ----------- | ----------- | ----------- | ----------- | ---------- |
| std::vector | 0.017308 s  | 0.166489 s  | 1.52005  s  | 17.329  s  |
|    Vector   | 0.0133609 s | 0.108366 s  | 0.931235 s  | 20.1476 s  |

## Realizuotos funkcijos

**vector::operator= copy version**
```ruby
Vector& operator=(const Vector& x)
{
	if (&x == this)
	{
        return *this;
    }
	clear();
	_data = _alloc.allocate(x.end() - x.begin());
	_size = _capacity = std::uninitialized_copy(x.begin(), x.end(), _data);
}
```
- Priskiria vieną vektorių kitam.

**vector::push_back**
```ruby
void push_back(const T & value)
{
	if (_size == _capacity)
	{
        grow();
    }
    _alloc.construct(_size++, value);
}
```
- Prideda narį į vektoriaus pabaigą
- Jei `_size` == `_capacity`, kviečiama `grow()` funkcija, kuri padidina `_capacity`

**vector::pop_back()**
```ruby
void pop_back()
{
    iterator it = _size;
	_alloc.destroy(--it);
	_size = it;
}
```
- Panaikina paskutinį vektoriaus narį ir sumažina `_size`

**vector::shrink_to_fit**
```ruby
void shrink_to_fit()
{
    iterator temp_data = _alloc.allocate(_size - _data), temp_size, temp_capacity;
	std::move(_data, _size, temp_data);
	temp_size = temp_capacity = temp_data + (_size - _data);
	clear();
	_data = temp_data;
	_size = temp_size;
	_capacity = temp_capacity;
}
```
- Sumažina galimą `_capacity` atminties vietą, prilygindamas ją užbildytai vektoriaus vietai

**vector::reserve**
```ruby
void reserve(size_t size)
{
	if (size > _capacity)
	{
        iterator temp_data = _alloc.allocate(size);
        iterator temp_size = std::uninitialized_copy(_data, _size, temp_data);
        clear();
         _data = temp_data;
         _size = temp_size;
         _capacity = _data + size;
    }
}
```
- Palieka atmintyje vietos

## Funkcijos, kurios dar nėra realizuotos
- **member functions**
```shell
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