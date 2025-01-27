'use client';
import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { Accordion } from 'react-bootstrap';
import Image from 'react-bootstrap/Image';
import { ReactComponent as TextIcon } from '../assets/icons/card-text.svg';
import { ReactComponent as ImgIcon } from '../assets/icons/img.svg';
import { ReactComponent as MicIcon } from '../assets/icons/mic.svg';
import AudioInputPlayer from '../components/AudioInputPlayer';
import { Formik } from 'formik';
import * as Yup from 'yup';

const CardEdit = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState(null);
    const [cardType, setCardType] = useState(0);
    const [image, setImage] = useState(null);
    const [audio, setAudio] = useState(null);

    // Gerar schema de validação condicionalmente
    const getValidationSchema = () => {
        const schemas = {
            0: Yup.object({
                front: Yup.string()
                    .required('A frente é obrigatória.')
                    .min(3, 'O título deve ter pelo menos 3 caracteres.'),
                back: Yup.string()
                    .required('O assunto é obrigatório.')
                    .min(3, 'O assunto deve ter pelo menos 3 caracteres.'),
            }),
            1: Yup.object({
                front: Yup.string()
                    .required('A frente é obrigatória.')
                    .min(3, 'O título deve ter pelo menos 3 caracteres.'),
                file: Yup.mixed()
                    .required('Uma imagem é obrigatória.')
                    .test('fileFormat', 'Formato não suportado.', (value) =>
                        value ? ['image/jpeg', 'image/png', 'image/gif'].includes(value.type) : false
                    ),
            }),
            2: Yup.object({
                front: Yup.string()
                    .required('A frente é obrigatória.')
                    .min(3, 'O título deve ter pelo menos 3 caracteres.'),
                audio: Yup.mixed().required('O áudio é obrigatório.'),
            }),
        };

        return schemas[cardType];
    };

    useEffect(() => {
        async function fetchData() {
            if (id) {
                try {
                    const response = await fetch(`http://localhost:3000/api/card/${id}`);
                    const result = await response.json();
                    setData(result);
                } catch (error) {
                    console.error('Error fetching data:', error);
                } finally {
                    setLoading(false);
                }
            } else {
                setLoading(false);
            }
        }

        fetchData();
    }, [id]);

    if (loading) {
        return (
            <Container>
                <h2>Loading...</h2>
            </Container>
        );
    }

    if (!data && id) {
        return (
            <Container>
                <h2>No data found</h2>
            </Container>
        );
    }

    return (
        <Container>
            <h2>Edição</h2>
            <Formik
                initialValues={{
                    front: data?.front || '',
                    back: data?.back?? '',
                    file: data?.file ?? null,
                    audio: null,
                }}
                validationSchema={getValidationSchema()}
                onSubmit={async (values, { setSubmitting }) => {
                    const formData = new FormData();
                    let url =''
                    formData.append('front', values.front);
                    if(cardType==0){
                        formData.append('back', values.back);
                        url= 'card'
                    }

                    try {
                        const response = await fetch(`http://localhost:3000/api/${url}/${id}`, {
                            method:'PUT',
                            body: formData,
                        });
                        if (!response.ok) {
                            throw new Error('Failed to upload image');
                        }else{
                            
                        }
                        
                    } catch (error) {
                        console.error('Error uploading image:', error);
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
                    setFieldValue,
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

                        <Accordion activeKey={String(cardType)}>
                            <Accordion.Item eventKey="0">
                                <Accordion.Header onClick={() => setCardType(0)}>
                                    Texto <TextIcon />
                                </Accordion.Header>
                                <Accordion.Body>
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
                                </Accordion.Body>
                            </Accordion.Item>

                            <Accordion.Item eventKey="1">
                                <Accordion.Header onClick={() => setCardType(1)}>
                                    Imagem <ImgIcon />
                                </Accordion.Header>
                                <Accordion.Body>
                                    <Form.Label>Selecione uma imagem</Form.Label>
                                    <Form.Control
                                        type="file"
                                        name="file"
                                        onChange={(e) => setFieldValue('file', e.target.files[0])}
                                        onBlur={handleBlur}
                                        isInvalid={touched.file && !!errors.file}
                                    />
                                    <Form.Control.Feedback type="invalid">
                                        {errors.file}
                                    </Form.Control.Feedback>
                                </Accordion.Body>
                            </Accordion.Item>

                            <Accordion.Item eventKey="2">
                                <Accordion.Header onClick={() => setCardType(2)}>
                                    Áudio <MicIcon />
                                </Accordion.Header>
                                <Accordion.Body>
                                    <AudioInputPlayer setAudio={(file) => setFieldValue('audio', file)} />
                                    {touched.audio && errors.audio && (
                                        <div className="text-danger">{errors.audio}</div>
                                    )}
                                </Accordion.Body>
                            </Accordion.Item>
                        </Accordion>

                        <Button variant="secondary" type="submit" size="lg" disabled={isSubmitting}>
                            {isSubmitting ? 'Salvando...' : 'Salvar'}
                        </Button>
                    </Form>
                )}
            </Formik>
        </Container>
    );
};

export default CardEdit;
