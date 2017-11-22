package annotation.accessors;

import annotation.EntityModelDecorator;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@EntityModelDecorator(decorator = annotation.accessors.processor.Setter.class)
public @interface Setter {

}
