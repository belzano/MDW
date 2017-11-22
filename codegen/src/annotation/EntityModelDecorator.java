package annotation;

import java.lang.annotation.*;

@Target(ElementType.ANNOTATION_TYPE)
@Retention(RetentionPolicy.RUNTIME)
@Repeatable(value = EntityModelDecorators.class)
public @interface EntityModelDecorator {
    Class<? extends EntityModelDecoratorInterface> decorator();
}
