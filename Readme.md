<h1 align="center">
	<a href="https://github.com/KeyC0de/ProxyPattern">Proxy Design Pattern</a>
</h1>
<hr>


What is a proxy? Dictionary says "The authority to represent someone else". hmmm... Ponder on that a bit and let's see how the "Name and Conquer" of Proxy applies to software design patterns.

The definition of the Proxy pattern goes like this:
> Provides a surrogate or placeholder for another object in order to control access to it.

Let's get the obvious stuff out of the way:

1. A proxy certainly provides another level of indirection to another "target" object that we basically want to access

That's it. I have nothing else that seems obvious from the definition alone. But after further investigation and coding I realize that a Proxy object is indeed useful when we want to lazy-instantiate an object, or when we want to hide the implementation details of the object. For whatever reason, but this often comes up in software, we represent a back-end highly technical object with a more user/programmer friendly front-end one. Same story.

There are 3 main scenarios where you would want to create a Proxy object:

1. <i>Remote proxy</i>: a Proxy object you get when the target object is in a remote server
2. <i>Virtual proxy</i>: basically a way to cache the object
3. <i>Protection proxy</i>: hide details of the target object from the client. In this case the clients are only aware of the public interface of the target class; no implementation details are published.

It is time to emphasize that a Proxy is not just a wrapper/adapter/facade class, as many rookie programmers seem to think at first. So supplementing our original assumption it is not just another wrapper (level of indirection), instead the Proxy object adds additional behavior to control access to the target object. The behavior added is dependent on the usecase.


## Design:

- have your target object/class created good and proper
- the Proxy object may either subclass the target object or contain an instance of it as a member, depending on how you want to structure it
- add behavior to the Proxy object and inside it call upon the target object's functions and use its state according to your demands


Additional nomenclature surrounding this pattern: SDK (an SDK to the outside developers), Monkey Patching or Object Augmentation pattern

A related pattern "The Decorator" is aka "Smart Proxy". It is used when you want to add functionality to an object, not by extending that object's type but at runtime (by supplying classes to it).

Proxy is a very frequently used Design Pattern, thus I recommend you get to know it like the back of your hand. It's pretty easy as well so you have no excuse! Study the commented example (code in C++) - it's pretty easy, you'll agree with me. As a last note, don't be hesitant/afraid to use it. It does have a multitude of usecases including yours.

I used Windows 8.1 x86_64, Visual Studio 2017, Modern C++17 to build the project. It should work on other platforms as well.


# Contribute

Please submit any bugs you find through GitHub repository 'Issues' page with details describing how to replicate the problem. If you liked it or you learned something new give it a star, clone it, laugh at it, contribute to it whatever. I appreciate all of it. Enjoy.


# License

Distributed under the GNU GPL V3 License. See "GNU GPL license.txt" for more information.


# Contact

email: *nik.lazkey@gmail.com*</br>
website: [*www.keyc0de.net*](www.keyc0de.net)

