import React, { useState, useEffect } from 'react';
import { useParams } from "react-router-dom";
import { Container } from 'react-bootstrap';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import { Formik } from 'formik';
import * as Yup from 'yup';
import CardsList from '../components/CardsList';

const DeckEdit = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState(null); // Para armazenar os dados da API
    // Schema de validação com Yup
    const validationSchema = Yup.object().shape({
        title: Yup.string()
            .required("O título é obrigatório.")
            .min(3, "O título deve ter pelo menos 3 caracteres."),
        subject: Yup.string()
            .required("O assunto é obrigatório.")
            .min(3, "O assunto deve ter pelo menos 3 caracteres."),
    });

    const handleSave = async (values, { setSubmitting }) => {
        try {
            const formData = new FormData();
            formData.append('title', values.title);
            formData.append('subject', values.subject);

            let response = (id == undefined) ? response = await fetch(`http://localhost:3000/api/deck`, {
                method: 'POST',
                body: formData,
            }) : await fetch(`http://localhost:3000/api/deck/${id}`, {
                method: 'PUT',
                body: formData,
            });

            const result = await response.json();
        } catch (error) {
            console.error('Erro ao salvar os dados:', error);
            alert("Erro ao salvar o baralho.");
        } finally {
            setSubmitting(false);
        }
    };
    useEffect(() => {
        async function fetchData() {
            if (id !== undefined) {
                try {
                    const response = await fetch(`http://localhost:3000/api/deck/${id}`);
                    const result = await response.json();
                    setData(result)
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
            <Container fluid="xl" responsive="xl">
                <h2>Loading...</h2>
            </Container>
        );
    }

    return (
        <Container>
            <h2>{id === undefined ? "Novo Baralho" : "Edição"}</h2>
            <Formik
                initialValues={data ? { title: data.title, subject: data.subject } : { title: '', subject: '' }}
                validationSchema={validationSchema}
                onSubmit={handleSave}
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
                            <Form.Label>Título</Form.Label>
                            <Form.Control
                                type="text"
                                name="title"
                                placeholder="Adicione o nome do baralho"
                                value={values.title}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.title && !!errors.title}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.title}
                            </Form.Control.Feedback>
                        </Form.Group>

                        <Form.Group className="mb-3" controlId="formBasicSubject">
                            <Form.Label>Assunto</Form.Label>
                            <Form.Control
                                type="text"
                                name="subject"
                                placeholder="Adicione o assunto"
                                value={values.subject}
                                onChange={handleChange}
                                onBlur={handleBlur}
                                isInvalid={touched.subject && !!errors.subject}
                            />
                            <Form.Control.Feedback type="invalid">
                                {errors.subject}
                            </Form.Control.Feedback>
                        </Form.Group>

                        {id !== undefined && (
                            <>
                            <h4>Cartões de Texto</h4>
                            <br></br>
                            <Form.Group className="mb-3">
                                <CardsList id={id} cards={data.cards?? []}  type={"card"}/>
                            </Form.Group>
                            <h4>Cartões de Imagem</h4>
                            <br></br>
                            <Form.Group className="mb-3">
                                <CardsList id={id} cards={data.images?? []}  type={"image"}/>
                            </Form.Group>
                            <h4>Cartões de Audio</h4>
                            <br></br>
                            <Form.Group className="mb-3">
                                <CardsList id={id} cards={data.audios?? []}  type={"audio"}/>
                            </Form.Group>
                            </>
                            
                        )}

                        <Button variant="secondary" type="submit" size="lg" disabled={isSubmitting}>
                            {isSubmitting ? "Salvando..." : "Salvar"}
                        </Button>
                    </Form>
                )}
            </Formik>
        </Container>
    );
};

export default DeckEdit;
