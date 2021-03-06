package annotation;

import java.lang.annotation.*;

@Target(ElementType.ANNOTATION_TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface EntityTypeDecorator {
    Class<? extends TypeDecorator>[] decorators() default {};
    Class<? extends Annotation>[] extend() default {};
}
