package generation.writer.accessors;

import annotation.accessors.Getter;
import annotation.accessors.GetterSetter;
import annotation.accessors.Setter;
import model.EntityDataField;

import java.lang.annotation.Annotation;
import java.util.HashSet;
import java.util.Set;

public class AccessorWriterHelper {
    public static boolean hasAnnotationGetter(EntityDataField field) {
        return !getAnnotations(field, Getter.class).isEmpty() || !getAnnotations(field, GetterSetter.class).isEmpty();
    }

    public static boolean hasAnnotationSetter(EntityDataField field) {
        return !getAnnotations(field, Setter.class).isEmpty() || !getAnnotations(field, GetterSetter.class).isEmpty();
    }

    public static Set<Annotation> getAnnotations(EntityDataField field, Class<? extends  Annotation> annotationType) {
        Set<Annotation> matches = new HashSet<>();
        for (Annotation annotation: field.getAnnotations()) {
            if (annotation.annotationType() == annotationType) {
                matches.add(annotation);
            }
        }
        return matches;
    }

}
