package annotation.serialization;

import annotation.EntityModelDecorator;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@EntityModelDecorator(decorator = annotation.serialization.processor.Serializable.class)
public @interface Serializable {
}
