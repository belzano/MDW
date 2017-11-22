package annotation.accessors;

import annotation.EntityModelDecorator;
import annotation.accessors.processor.Getter;
import annotation.accessors.processor.Setter;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@EntityModelDecorator(decorator = Getter.class)
@EntityModelDecorator(decorator = Setter.class)
public @interface GetterSetter {
}
