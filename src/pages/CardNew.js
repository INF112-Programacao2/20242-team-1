'use client';
import React, { useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { Formik } from 'formik';
import * as Yup from 'yup';

const CardNew = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(false);

    if (loading) {
        return (
            <Container>
                <h2>Loading...</h2>
            </Container>
        );
    }

    const validationSchema = Yup.object({
        front: Yup.string()
            .required('A frente é obrigatória.')
            .min(3, 'O título deve ter pelo menos 3 caracteres.'),
        back: Yup.string()
            .required('O assunto é obrigatório.')
            .min(3, 'O assunto deve ter pelo menos 3 caracteres.'),
    });

    return (
        <Container>
            <h2>Novo Cartão de Texto</h2>
            <Formik
                initialValues={{
                    front: '',
                    back: '',
                }}
                validationSchema={validationSchema}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    formData.append('front', values.front);
                    formData.append('back', values.back);
                    formData.append('deckId', id);

                    try {
                        const response = await fetch(`http://localhost:3000/api/card`, {
                            method: 'POST',
                            body: formData,
                        });

                        if (!response.ok) {
                            throw new Error('Falha ao salvar o cartão de texto');
                        }
                    } catch (error) {
                        console.error('Erro ao salvar o cartão:', error);
                    }

                    setSubmitting(false);
                }}
            >
                {({
                    values,
                    errors,
                    touched,
                    handleChange,
                    handleBlur,
                    handleSubmit,
                    isSubmitting,
                }) => (
                    <Form onSubmit={handleSubmit}>
                        <Form.Group className="mb-3" controlId="formBasicTitle">
                            <Form.Label>Frente</Form.Label>
                            <Form.Control
                                type="text"
                                name="front"
                                placeholder="Adicione a frente do cartão"
                                value={values.front}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.front && !!errors.front}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.front}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Form.Group className="mb-3" controlId="formBasicBack">
                            <Form.Label>Assunto</Form.Label>
                            <Form.Control
                                type="text"
                                name="back"
                                placeholder="Adicione o assunto"
                                value={values.back}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.back && !!errors.back}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.back}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Button variant="secondary" type="submit" size="lg" disabled={isSubmitting}>
                            {isSubmitting ? 'Salvando...' : 'Salvar'}
                        </Button>
                    </Form>
                )}
            </Formik>
        </Container>
    );
};

export default CardNew;
