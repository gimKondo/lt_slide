### タイトル


テンプレート


---

### Itemization

- level1 a
    - level2
        - level3
- level1 b
    - level2
- level1 c

---


### Ruby

```ruby
class Hoge
  # mixin some module
  include SomeModule
  def foo()
    return 1
  end
end
```

+++


### C++

```cpp
class Hoge {
private:
  int foo(double a) {
    return 1;
  }
public:
  // constructor
  Hoge() {}
};
```

---

### Elixir

```elixir
defmodule Hoge
  # public function
  def public_func(arg) do
    private_func(arg)
  end
  # internal function
  defp private_func(arg) do
    arg
  end
end
```
@[1,10](モジュール定義)
@[2-5](公開関数の定義)
@[6-9](内部関数の定義)
