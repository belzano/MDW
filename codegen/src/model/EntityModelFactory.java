package model;

import annotation.EntityModelDecorator;
import annotation.EntityModelDecoratorInterface;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Set;
import java.util.stream.Collectors;

public class EntityModelFactory {

    public EntityModelContext generate(Set<Class<?>> codeGenClasses) throws Exception {

        Set<EntityModel> models = codeGenClasses.stream().map(EntityModel::new).collect(Collectors.toSet());
        EntityModelContext context = new EntityModelContext(models);

        for (EntityModel model: context.getEntityModels()) {

            for (Annotation annotation : model.getEntityClass().getAnnotations()) {
                EntityModelDecorator codegenAnnotation = asEntityModelDecorator(annotation);
                if (codegenAnnotation == null) {
                    continue;
                }
                EntityModelDecoratorInterface processor = getProcessor(codegenAnnotation);
                processor.updateModel(model, context);
            }

            for (Field field: model.getEntityClass().getDeclaredFields()) {
                for (Annotation annotation : field.getAnnotations()) {
                    EntityModelDecorator codegenAnnotation = asEntityModelDecorator(annotation);
                    if (codegenAnnotation == null) {
                        continue;
                    }
                    EntityModelDecoratorInterface processor = getProcessor(codegenAnnotation);
                    processor.updateModel(model, context);
                }
            }
        }
        return context;
    }

    EntityModelDecorator asEntityModelDecorator(Annotation annotation) {
        EntityModelDecorator codegenAnnotation = annotation.annotationType().getAnnotation(EntityModelDecorator.class);
        return codegenAnnotation;
    }

    EntityModelDecoratorInterface getProcessor(EntityModelDecorator codegenAnnotation) throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Class<? extends EntityModelDecoratorInterface> clazz = codegenAnnotation.decorator();
        Constructor<? extends EntityModelDecoratorInterface> ctor = clazz.getConstructor();
        EntityModelDecoratorInterface processor = ctor.newInstance();
        return processor;
    }

}
