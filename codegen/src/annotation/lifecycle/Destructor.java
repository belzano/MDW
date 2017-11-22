package annotation.lifecycle;

import annotation.EntityModelDecorator;

import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@EntityModelDecorator(decorator = annotation.lifecycle.processor.Destructor.class)
public @interface Destructor {
}
