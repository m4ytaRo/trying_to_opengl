## Слоты

### Проблема

Известно, что OpenGL - state machine. 
Представим, что нам нужно использовать несколько текстур в одном фрагментном шейдере. 
Если у OpenGL будет один стейт текстуры, то при, например, наложении текстур придется перебиндить текстуру несколько раз. Вместо этого хотелось бы иметь доступ к нескольим текстурам сразу. 

Для этой цели были придуманы слоты, или Texture units

### Texture units (slots)

В сущности представляют собой часть OpenGL контекста

Можно представить как структуры, которые содержат в себе таргеты - типы текстур, на которые можно забиндить одну текстуру
Примерная схема:

![](assets/2026-04-04-14-20-57-image.png)

### Код

Работа начинается с создания объекта текстуры

```cpp
glGenTextures(1, &ID);
```

```cpp
glActiveTexture(slot); // биндим активный слот
glBindTexture(texType, ID); // работаем внутри слота, по 
//нужному типу биндим ID текстуры
```

Все дальнейшие операции производятся с объектом текстуры, который достигается по цепочке из текущего стейта
TEXTURE UNIT -> TEXTURE TARGET -> ID -> TEXTURE OBJECT

```cpp
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);

    glGenerateMipmap(texType);
```

Разберем подробно настройку текстуры

```cpp
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
```

Фильтры при уменьшении и увеличении текстуры.

Таблицу типов приводить лень, читай здесь: [OpenGL - Textures](https://open.gl/textures)
Вот 2 варианта для примера

![](assets/2026-04-04-14-36-38-image.png)

Дальше

```cpp
glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
```

То есть это описание поведения, когда текстурные координаты выходят за пределы [0,1]

![](assets/2026-04-04-14-38-12-image.png)

```cpp
glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
```

Загружает данные текстуры передаются в видеопамять, связанную с объектом текстуры

Далее генерим мипмапы

```cpp
glGenerateMipmap(texType);
```

Для mipmap создается $floor(log2(max(width, height))) + 1$ изображений

Напомним, что **Mipmap** — это цепочка уменьшенных копий текстуры для оптимизации в зависимости от дистанции рендера

![](assets/2026-04-04-14-50-17-image.png)

### Ограничения

Спецификация явно запрещает использование двух разных типов семплеров из одного текстурного блока. Предполагаемый результат : undefined behaviour
Пример:

```cpp
uniform sampler2D tex0;
uniform sampler3D tex1;

... // где то после shaderProgram.activate() по несчастливой случайности:
glUniform1i(texUni0, unit);
glUniform1i(texUni1, unit);
```
