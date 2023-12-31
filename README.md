# 3DViewer
-- Описание:
- 3DViewer - это проект для просмотра 3D моделей, созданный с использованием фреймворка Qt. Он предоставляет пользователю интуитивный интерфейс для загрузки и визуализации различных 3D моделей в реальном времени.
- Реализовано на языке программирования С++

## Qt: 3DViewer разработан с использованием фреймворка Qt.

### Архитектура
#### Проект разработан с использованием паттерна проектирования MVC (Model-View-Controller):

- Model: Отвечает за данные, связанные с 3D моделями, их обработку и загрузку.
- View: Отображает 3D модели в графическом интерфейсе.
- Controller: Управляет взаимодействием между Моделью и Представлением, обрабатывает пользовательский ввод.

### Паттерны проектирования
#### В проекте реализованы следующие паттерны проектирования:

- Observer: Позволяет объектам подписываться на уведомления о событиях, происходящих в других объектах, обеспечивая тем самым динамичное взаимодействие компонентов.

- Singleton: Гарантирует, что у класса есть только один экземпляр, и предоставляет глобальную точку доступа к этому экземпляру.

- Strategy: Определяет семейство алгоритмов, инкапсулирует каждый из них и обеспечивает их взаимозаменяемость.
