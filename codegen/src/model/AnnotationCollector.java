package model;

import annotation.EntityFieldDecorator;
import annotation.EntityTypeDecorator;
import annotation.FieldDecorator;
import annotation.TypeDecorator;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class AnnotationCollector {


    public static Set<Class<? extends Annotation>> collectClassEntityTypeAnnotation(Class<?> clazz) {
        Set<Class<? extends Annotation>> codegenAnnotations = new HashSet<>();
        for (Annotation annotation : clazz.getAnnotations()) {
            codegenAnnotations.addAll(collectEntityType(annotation.annotationType()));
        }
        return codegenAnnotations;
    }

    private static Set<Class<? extends Annotation>> collectEntityType(Class<? extends Annotation> rootAnnotation) {
        Set<Class<? extends Annotation>> decorators = new HashSet<>();

        EntityTypeDecorator asTypeDecorator = rootAnnotation.getAnnotation(EntityTypeDecorator.class);
        if (asTypeDecorator == null) {
            return decorators;
        }
        decorators.add(rootAnnotation);

        for (Class<? extends Annotation> annotation : asTypeDecorator.extend()) {
            EntityTypeDecorator asTypeDecoratorChild = annotation.getAnnotation(EntityTypeDecorator.class);
            if (asTypeDecoratorChild == null) {
                continue;
            }
            decorators.add(annotation);

            for (Class<? extends Annotation> extender : asTypeDecoratorChild.extend()) {
                decorators.addAll(collectEntityType(extender));
            }

        }
        return decorators;
    }

    public static List<TypeDecorator> getEntityTypeProcessors(Set<Class<? extends Annotation>> annotations) {
        List<TypeDecorator> result = new ArrayList<>();
        for (Class<? extends Annotation> annotation : annotations) {
            EntityTypeDecorator codegenAnnotation = annotation.getAnnotation(EntityTypeDecorator.class);
            if (codegenAnnotation == null) {
                continue;
            }

            Class<? extends TypeDecorator>[] clazzes = codegenAnnotation.decorators();
            for (Class<? extends TypeDecorator> clazz : clazzes) {
                try {
                    Constructor<? extends TypeDecorator> ctor = clazz.getConstructor();
                    result.add(ctor.newInstance());
                } catch (Exception ex) {
                    System.out.println(ex);
                }
            }
        }
        return result;
    }


    public static Set<Class<? extends Annotation>> collectFieldTypeAnnotation(Field field) {
        Set<Class<? extends Annotation>> codegenAnnotations = new HashSet<>();
        for (Annotation annotation : field.getAnnotations()) {
            codegenAnnotations.addAll(collectFieldType(annotation.annotationType()));
        }
        return codegenAnnotations;
    }

    static Set<Class<? extends Annotation>> collectFieldType(Class<? extends Annotation> rootAnnotation) {
        Set<Class<? extends Annotation>> decorators = new HashSet<>();

        EntityFieldDecorator asTypeDecorator = rootAnnotation.getAnnotation(EntityFieldDecorator.class);
        if (asTypeDecorator == null) {
            return decorators;
        }
        decorators.add(rootAnnotation);

        for (Class<? extends Annotation> annotation : asTypeDecorator.extend()) {
            EntityFieldDecorator asTypeDecoratorChild = annotation.getAnnotation(EntityFieldDecorator.class);
            if (asTypeDecoratorChild == null) {
                continue;
            }
            decorators.add(annotation);

            for (Class<? extends Annotation> extender : asTypeDecoratorChild.extend()) {
                decorators.addAll(collectFieldType(extender));
            }

        }
        return decorators;
    }

    public static List<FieldDecorator> getFieldTypeProcessors(Set<Class<? extends Annotation>> annotations)  {
        List<FieldDecorator> result = new ArrayList<>();
        for (Class<? extends Annotation> annotation : annotations) {
            EntityFieldDecorator codegenAnnotation = annotation.getAnnotation(EntityFieldDecorator.class);
            if (codegenAnnotation == null) {
                continue;
            }

            Class<? extends FieldDecorator>[] clazzes = codegenAnnotation.decorators();
            for (Class<? extends FieldDecorator> clazz : clazzes) {
                try {
                    Constructor<? extends FieldDecorator> ctor = clazz.getConstructor();
                    result.add(ctor.newInstance());
                } catch (Exception ex) {
                    System.out.println(ex);
                }
            }
        }
        return result;
    }
}
