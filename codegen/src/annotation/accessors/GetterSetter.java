package annotation.accessors;

import annotation.EntityFieldDecorator;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@EntityFieldDecorator(decorators = {Getter.Decorator.class, Setter.Decorator.class})
public @interface GetterSetter {

}
