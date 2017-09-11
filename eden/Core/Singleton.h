#pragma once

namespace edn
{
    /**
     * Inhereting from singleton to make your class a singleton.
     * Singleton class will be created at applciation startup, before
     * the main execution. There is no way to determine the order of
     * initalization, therefore you have to make sure that your singleton
     * class initializes to a 'clean' state. if you want to 'create'/'setup'
     * the singleton create initialize and shutdown functions that take the
     * singleton initialization information. Make sure that you have a way
     * to cleanup the singleton once you are done with it as well.
     *
     * This singleton implementation removes the need to call the 'instance'
     * of the singleton. Simply calling the singleton name gives you the instance.
     * Because os this, Singletons must be declared in a special way
     *
     * Sample:
     * static class Application : public Singleton<class Application>
     * {
     *     void setup();    // Example functions
     *     void shutdown(); // Example functions
     *     ....
     * } &Application = Singleton<class Application>::instanceRef;
     *
     * Application.setup();
     * ...
     * Application.setup();
     */
    template<class T>
    class Singleton
    {
    public:
        static T& instanceRef;

    protected:
        explicit Singleton() {}
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

    private:
        static T instance;
    };

    template<class T>
    T Singleton<T>::instance;

    template<class T>
    T& Singleton<T>::instanceRef = Singleton<T>::instance;
}
