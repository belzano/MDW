package model;

import annotation.EntityTypeDecorator;
import annotation.TypeDecorator;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class EntityModelFactory {

    public EntityModelContext generate(Set<Class<?>> codeGenClasses) throws Exception {

        EntityModelContext context = new EntityModelContext();

        for (Class<?> clazz : codeGenClasses) {

            if (! hasEntityTypeAnnotation(clazz)) {
                continue;
            }

            EntityTypeModel model = new EntityTypeModel(clazz);
            context.getEntityModels().add(model);


            for (Annotation annotation : clazz.getAnnotations()) {

                EntityTypeDecorator codegenAnnotation = asTypeDecorator(annotation);
                if (codegenAnnotation == null) {
                    continue;
                }

                for (TypeDecorator processor : getProcessors(codegenAnnotation)) {
                    processor.updateModel(model, context);
                }
            }

        }
        return context;
    }

    boolean hasEntityTypeAnnotation(Class<?> clazz) {
        for (Annotation annotation : clazz.getAnnotations()) {
            EntityTypeDecorator codegenAnnotation = asTypeDecorator(annotation);
            if (codegenAnnotation != null) {
                return true;
            }
        }
        return false;
    }
//
//    Set<Class<? extends EntityTypeDecorator>> getEntityTypeDecoratorAnnotations(Annotation root) {
//        Set<Class<? extends EntityTypeDecorator>> result = new HashSet<>();
//
//        if (root instanceof EntityTypeDecorator) {
//            result.add(((EntityTypeDecorator)root).getClass());
//        }
//
//        EntityTypeDecorator codegenAnnotation = root.annotationType().getAnnotation(EntityTypeDecorator.class);
//        if (codegenAnnotation != null){
//            result.add(codegenAnnotation.getClass());
//        }
//
//        EntityTypeDecorators codegenAnnotations = root.annotationType().getAnnotation(EntityTypeDecorators.class);
//        if (codegenAnnotations != null) {
//            for (Annotation annotation : codegenAnnotations.value()) {
//                result.addAll(getEntityTypeDecoratorAnnotations(annotation));
//            }
//        }
//        return result;
//    }

    EntityTypeDecorator asTypeDecorator(Annotation annotation) {
        EntityTypeDecorator codegenAnnotation = annotation.annotationType().getAnnotation(EntityTypeDecorator.class);
        return codegenAnnotation;
    }

    List<TypeDecorator> getProcessors(EntityTypeDecorator codegenAnnotation) throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Class<? extends TypeDecorator>[] clazzes = codegenAnnotation.decorators();
        List<TypeDecorator> result = new ArrayList<>();
        for (Class<? extends TypeDecorator> clazz : clazzes) {
            Constructor<? extends TypeDecorator> ctor = clazz.getConstructor();
            result.add(ctor.newInstance());
        }
        return result;
    }

}
