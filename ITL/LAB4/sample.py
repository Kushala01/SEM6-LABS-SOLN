class Human:
    # A class attribute. It is shared by all instances of this class
    species = "H. sapiens"

    # Basic initializer, called when this class is instantiated.
    def __init__(self, name):
        # Assign the argument to the instance's name attribute
        self.name = name
        # Initialize property
        self._age = 0

    # An instance method.
    def say(self, msg):
        print("{name}: {message}".format(name=self.name, message=msg))

    # Another instance method
    def sing(self):
        return 'yo... yo... microphone check... one two... one two...'

    # A class method shared among all instances
    @classmethod
    def get_species(cls):
        return cls.species

    # A static method called without a class or instance reference
    @staticmethod
    def grunt():
        return "*grunt*"

    # A property like a getter, read-only attribute
    @property
    def age(self):
        return self._age

    # Setter for the property
    @age.setter
    def age(self, age):
        self._age = age

    # Deleter for the property
    @age.deleter
    def age(self):
        del self._age

if __name__ == '__main__':
    # Instantiate a class
    i = Human(name="Ian")
    i.say("hi")  # "Ian: hi"
    
    j = Human("Joel")
    j.say("hello")  # "Joel: hello"
    
    # Call class method
    i.say(i.get_species())  # "Ian: H. sapiens"
    
    # Change the shared attribute
    Human.species = "H. neanderthalensis"
    i.say(i.get_species())  # => "Ian: H. neanderthalensis"
    j.say(j.get_species())  # => "Joel: H. neanderthalensis"
    
    # Call static method
    print(Human.grunt())  # => "*grunt*"
    
    # Cannot call static method with instance of object
    # because i.grunt() will automatically put "self" (the object i) as an argument
    # print(i.grunt())  # => TypeError: grunt() takes 0 positional arguments but 1 was given
    
    # Update the property for this instance
    i.age = 42
    # Get the property
    i.say(i.age)  # => "Ian: 42"
    j.say(j.age)  # => "Joel: 0"
    
    # Delete the property
    del i.age  # => this would raise an AttributeError
